/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:34:20 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/14 15:48:14 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node_curr;
	t_list	*node_next;

	if (!lst || !del)
		return ;
	node_curr = *lst;
	while (node_curr)
	{
		node_next = node_curr->next;
		del(node_curr->content);
		free(node_curr);
		node_curr = node_next;
	}
	*lst = NULL;
}
