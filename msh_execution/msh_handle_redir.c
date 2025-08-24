/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 07:14:36 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/24 20:00:44 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

static int	static_open_file(const t_red_node *redir_node, bool is_child);
static int	static_redir_apply(const t_red_node *current, bool is_child);

int	msh_handle_redir(const t_red_node *redir_list, bool is_child)
{
	const t_red_node	*current;

	current = redir_list;
	while (current)
	{
		if (current->is_ambiguous)
		{
			msh_print_error(current->val, "ambiguous redirect");
			if (is_child)
				exit(EXIT_FAILURE);
			else
				return (EXIT_FAILURE);
		}
		if (static_redir_apply(current, is_child) == EXIT_FAILURE)
		{
			if (is_child)
				exit(EXIT_FAILURE);
			else
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

static int	static_open_file(const t_red_node *redir_node, bool is_child)
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
	{
		msh_perror(redir_node->val);
		if (is_child)
			exit(EXIT_FAILURE);
	}
	return (fd);
}

static int	static_redir_apply(const t_red_node *current, bool is_child)
{
	int	fd;

	fd = static_open_file(current, is_child);
	if (fd == -1)
		return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}
