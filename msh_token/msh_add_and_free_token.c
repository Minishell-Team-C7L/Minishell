/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_add_and_free_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:48:50 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/07 05:25:52 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_token.h"

void	token_list_add(t_token **list, t_token *new_token)
{
	t_token	*curr_list;

	if (!*list)
	{
		*list = new_token;
		return ;
	}
	curr_list = *list;
	while (curr_list && curr_list->next)
		curr_list = curr_list->next;
	curr_list->next = new_token;
	new_token->prev = curr_list;
}

void	free_token_list(t_token **token_list)
{
	t_token	*curr_node;
	t_token	*next;

	curr_node = *token_list;
	if (!curr_node)
		return ;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		free(curr_node->val);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*token_list = NULL;
}

int	msh_is_operator(char *op)
{
	if (*op == '<' || *op == '>'
		|| *op == '|')
		return (1);
	return (0);
}
