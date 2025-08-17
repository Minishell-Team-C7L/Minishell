/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 02:26:15 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/17 13:13:39 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

static int	static_single_heredoc(t_data *data, t_red_node *redir);
static void	static_heredoc_child(
				t_data *data, t_red_node *redir, char *tmp_filename);
static char	*static_temp_file(t_data *data);
static bool	static_add_to_cleanup(char *filename, t_data *data);

int	msh_handle_heredocs(t_data *data, t_node *node)
{
	t_red_node	*current_redir;

	if (!node)
		return (EXIT_SUCCESS);
	if (node->type == CMD_N)
	{
		current_redir = node->red_l;
		while (current_redir)
		{
			if (current_redir->type == HEREDOC_RED)
			{
				if (static_single_heredoc(data, current_redir) != EXIT_SUCCESS)
					return (EXIT_FAILURE);
			}
			current_redir = current_redir->next;
		}
	}
	if (node->left)
		if (msh_handle_heredocs(data, node->left) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	if (node->right)
		if (msh_handle_heredocs(data, node->right) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static bool	msh_heredoc_delimiter_check(char *read_line, char *del)
{
	if (!del)
		return (false);
	while (*read_line)
	{
		if (*del == '"' || *del == '\'')
		{
			del++;
			continue ;
		}
		else if (*read_line == *del)
		{
			del++;
			read_line++;
		}
		else
			return (false);
	}
	while (*del == '"' || *del == '\'')
		del++;
	return (!ft_strcmp(read_line, del));
}

static int	static_single_heredoc(t_data *data, t_red_node *redir)
{
	char	*tmp_filename;
	pid_t	pid;
	int		status;

	tmp_filename = static_temp_file(data);
	if (!tmp_filename)
		return (msh_perror("heredoc"));
	pid = fork();
	if (pid == FORK_FAILURE)
		return (msh_perror("fork"));
	if (pid == IS_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		static_heredoc_child(data, redir, tmp_filename);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		unlink(tmp_filename);
		ft_free((void **)&tmp_filename);
		// data->exit_status = 130;
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_free((void **)&redir->val);
	redir->type = IN_RED;
	redir->val = tmp_filename;
	return (EXIT_SUCCESS);
}

static void	static_heredoc_child(
	t_data *data, t_red_node *redir, char *tmp_filename)
{
	char	*line;
	int		tmp_fd;

	tmp_fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (tmp_fd == -1)
		exit(msh_perror(tmp_filename));
	while (true)
	{
		msh_ctrl_line_off(data);
		line = readline("> ");
		if (!line)
			break ;
		if (msh_heredoc_delimiter_check(line, redir->val))
		{
			free(line);
			break ;
		}
		msh_expand_heredoc(tmp_fd, line, data, redir->heredoc_sign);
		free(line);
	}
	close(tmp_fd);
	exit(EXIT_SUCCESS);
}

static char	*static_temp_file(t_data *data)
{
	char	*pid_str;
	char	*count_str;
	char	*temp_prefix;
	char	*filename;

	pid_str = ft_itoa(getpid());
	count_str = ft_itoa(data->heredoc_count++);
	if (!pid_str || !count_str)
	{
		ft_free((void **)&pid_str);
		ft_free((void **)&count_str);
		return (NULL);
	}
	temp_prefix = ft_strjoin("/tmp/msh_heredoc_", pid_str);
	ft_free((void **)&pid_str);
	if (!temp_prefix)
		return (ft_free((void **)&count_str), NULL);
	filename = ft_strjoin(temp_prefix, count_str);
	ft_free((void **)&temp_prefix);
	ft_free((void **)&count_str);
	if (!filename || !static_add_to_cleanup(filename, data))
		return (ft_free((void **)&filename), NULL);
	return (filename);
}

static bool	static_add_to_cleanup(char *filename, t_data *data)
{
	t_list	*new_node;

	new_node = ft_lstnew(filename);
	if (!new_node)
		return (false);
	ft_lstadd_back(&data->heredoc_files, new_node);
	return (true);
}
