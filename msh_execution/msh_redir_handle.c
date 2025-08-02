/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 07:14:36 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/02 09:50:44 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

static int	static_open_file(const t_red_node *redir_node);

void	msh_redir_handle(const t_red_node *redir_list)
{
	const t_red_node	*current;
	int					fd;

	current = redir_list;
	while (current)
	{
		fd = static_open_file(current);
		if (current->type == IN_RED || current->type == HEREDOC_RED)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				exit(msh_perror("dup2"));
		}
		else if (current->type == OUT_RED || current->type == APPEND_RED)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
				exit(msh_perror("dup2"));
		}
		close(fd);
		current = current->next;
	}
}

static int	static_open_file(const t_red_node *redir_node)
{
	int	fd;

	fd = -1;
	if (redir_node->type == IN_RED)
		fd = open(redir_node->val, O_RDONLY);
	else if (redir_node->type == OUT_RED)
		fd = open(redir_node->val, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (redir_node->type == APPEND_RED)
		fd = open(redir_node->val, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (redir_node->type == HEREDOC_RED)
		fd = open(redir_node->val, O_RDONLY);
	if (fd == -1)
		exit(msh_perror(redir_node->val));
	return (fd);
}

// -----------------------------------------------------------------------------

static int	static_single_heredoc(t_red_node *redir)
{
	char	*line;
	int		tmp_fd;
	char	*tmp_filename;

	tmp_filename = msh_create_temp_file();
	if (!tmp_filename)
		return (msh_perror("heredoc"));
	tmp_fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (tmp_fd == -1)
		return (msh_perror(tmp_filename));
	while (true)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->val) == 0)
			break ;
		ft_putstr_fd(line, tmp_fd);
		ft_putstr_fd("\n", tmp_fd);
		free(line);
	}
	free(line);
	close(tmp_fd);
	ft_free((void **)&redir->val);
	redir->type = IN_RED;
	redir->val = tmp_filename;
	return (EXIT_SUCCESS);
}

int	msh_handle_heredocs(t_node *node)
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
				if (static_single_heredoc(current_redir) != EXIT_SUCCESS)
					return (EXIT_FAILURE);
			}
			current_redir = current_redir->next;
		}
	}
	if (node->left)
		if (msh_handle_heredocs(node->left) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	if (node->right)
		if (msh_handle_heredocs(node->right) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
