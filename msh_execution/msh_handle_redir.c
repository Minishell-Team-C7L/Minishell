/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 07:14:36 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/22 11:54:16 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

static int	static_open_file(const t_red_node *redir_node);

void	msh_handle_redir(const t_red_node *redir_list)
{
	const t_red_node	*current;
	int					fd;

	current = redir_list;
	while (current)
	{
		// if (current->is_ambiguous)
		// {
		// 	msh_puterr(current->val, "ambiguous redirect");
		// 	exit(EXIT_FAILURE);
		// }
		fd = static_open_file(current);
		if (current->type == IN_RED)
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
	if (fd == -1)
		exit(msh_perror(redir_node->val));
	return (fd);
}
