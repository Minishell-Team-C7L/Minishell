/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_add_and_free_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:48:50 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/06 06:40:03 by lhchiban         ###   ########.fr       */
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
	t_token	*current;
	t_token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		next = current->next;
		if (current->val)
			free(current->val);
		free(current);
		current = next;
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
