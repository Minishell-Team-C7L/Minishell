/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 07:14:36 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/30 10:40:50 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

// Returns 0 on success, or exits the child on failure.
static int	static_open_file(t_red_node *redir_node)
{
	int	fd;

	fd = -1;
	if (redir_node->type == IN_RED)
		fd = open(redir_node->val, O_RDONLY);
	else if (redir_node->type == OUT_RED)
		fd = open(redir_node->val, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir_node->type == APPEND_RED)
		fd = open(redir_node->val, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir_node->type == HEREDOC_RED)
		fd = open(redir_node->val, O_RDONLY);
	if (fd == -1)
		exit(msh_perror(redir_node->val));
	return (fd);
}

void	msh_handle_redirections(t_red_node *redir_list)
{
	t_red_node	*current;
	int			fd;

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