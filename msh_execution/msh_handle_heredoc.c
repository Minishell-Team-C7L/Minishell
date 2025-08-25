/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 02:26:15 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/25 10:14:20 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

static int	static_single_heredoc(t_data *data, t_red_node *redir);
static char	*static_temp_file(t_data *data);
static void	static_heredoc_child(
				t_data *data, t_red_node *redir, char *tmp_filename);
static bool	msh_heredoc_delimiter_check(char *read_line, char *del);

int	msh_handle_heredocs(t_data *data, t_node *node)
{
	t_red_node	*current_redir;

	if (!node)
		return (EXIT_SUCCESS);
	if (node->type == PIPE_N)
	{
		if (msh_handle_heredocs(data, node->left) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (msh_handle_heredocs(data, node->right) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
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
	return (EXIT_SUCCESS);
}

int	static_single_heredoc(t_data *data, t_red_node *redir)
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
		(signal(SIGINT, SIG_DFL),
			static_heredoc_child(data, redir, tmp_filename));
	(signal(SIGINT, SIG_IGN), waitpid(pid, &status, 0));
	if (WIFSIGNALED(status))
	{
		(unlink(tmp_filename), ft_free((void **)&tmp_filename));
		if (WTERMSIG(status) == SIGINT)
			msh_puterr("\n");
		return (EXIT_FAILURE);
	}
	ft_free((void **)&redir->val);
	redir->type = IN_RED;
	redir->val = tmp_filename;
	return (EXIT_SUCCESS);
}

static char	*static_temp_file(t_data *data)
{
	char	*filename;
	char	*pid_str;
	char	*count_str;
	t_list	*new_node;

	pid_str = ft_itoa((int)&filename);
	count_str = ft_itoa(data->heredoc_count++);
	if (!pid_str || !count_str)
		return (ft_free((void **)&pid_str), ft_free((void **)&count_str), NULL);
	filename = ft_strjoin("/tmp/msh_heredoc_", pid_str);
	ft_free((void **)&pid_str);
	if (!filename)
		return (ft_free((void **)&count_str), NULL);
	pid_str = ft_strjoin(filename, count_str);
	ft_free((void **)&filename);
	ft_free((void **)&count_str);
	filename = pid_str;
	if (!filename)
		return (NULL);
	new_node = ft_lstnew(filename);
	if (!new_node)
		return (ft_free((void **)&filename), NULL);
	ft_lstadd_back(&data->heredoc_files, new_node);
	return (filename);
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
			break ;
		msh_expand_heredoc(tmp_fd, line, data, redir->heredoc_exp);
		ft_putchar_fd('\n', tmp_fd);
		free(line);
	}
	close(tmp_fd);
	exit(EXIT_SUCCESS);
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
