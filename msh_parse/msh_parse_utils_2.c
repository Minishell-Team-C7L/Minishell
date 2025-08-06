/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:49:32 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/06 06:53:04 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

t_red_type	msh_red_type(t_token_types type)
{
	if (REDIR_APPEND_T == type)
		return (APPEND_RED);
	if (REDIR_IN_T == type)
		return (IN_RED);
	if (REDIR_OUT_T == type)
		return (OUT_RED);
	return (HEREDOC_RED);
}

void	msh_combine_rediractions(t_red_node *n_red, t_red_node **red_list)
{
	t_red_node	*cur_red;

	if (!*red_list)
	{
		*red_list = n_red;
		return ;
	}
	cur_red = *red_list;
	while (cur_red && cur_red->next)
		cur_red = cur_red->next;
	cur_red->next = n_red;
}

void	msh_clear_cmd(t_node *cmd_node)
{
	if (!cmd_node)
		return ;
	msh_red_list_clear(&(cmd_node->red_l));
	msh_free_cmd_args(cmd_node);
	ft_free ((void **)&cmd_node->arg);
}

void	msh_red_list_clear(t_red_node **red_list)
{
	t_red_node	*cur_node;
	t_red_node	*next_node;

	if (!red_list || !*red_list)
		return ;
	cur_node = *red_list;
	while (cur_node)
	{
		next_node = cur_node->next;
		if (cur_node->val)
			free(cur_node->val);
		free(cur_node);
		cur_node = next_node;
	}
	*red_list = NULL;
}

int	msh_is_red(t_token_types t_type)
{
	if (t_type == REDIR_APPEND_T
		|| t_type == REDIR_IN_T
		|| t_type == HERE_DOC_T
		|| t_type == REDIR_OUT_T)
		return (1);
	return (0);
}
