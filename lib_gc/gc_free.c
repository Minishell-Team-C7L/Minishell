/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:20:14 by aessaber          #+#    #+#             */
/*   Updated: 2025/06/02 17:05:48 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"

void	gc_free(t_gc *gc_node)
{
	t_gc	*gc_temp;

	while (gc_node)
	{
		gc_temp = gc_node;
		gc_node = gc_node->next;
		free(gc_temp->ptr);
		free(gc_temp);
	}
}

void	msh_malloc(void **ptr, size_t size, t_gc **gc_head)
{
	*ptr = gc_malloc(size, gc_head);

	if (!*ptr)
	{
		gc_free(*gc_head);
		perror("msh");
		exit(2);
	}
}
