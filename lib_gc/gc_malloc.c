/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:38:53 by aessaber          #+#    #+#             */
/*   Updated: 2025/06/02 17:04:48 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"

void	*gc_malloc(size_t size, t_gc **gc_head)
{
	void	*ptr;
	t_gc	*node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc));
	if (!node)
		return (free(ptr), NULL);
	node->ptr = ptr;
	node->next = *gc_head;
	*gc_head = node;
	return (ptr);
}
