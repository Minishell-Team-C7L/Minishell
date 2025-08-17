/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:38:53 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 05:01:35 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"

void	*gc_malloc(size_t size, t_gc **gc)
{
	t_alloc	*new_alloc;

	if (!gc || !*gc)
		return (dbg_nullarg(__func__), NULL);
	new_alloc = malloc(sizeof(t_alloc));
	if (!new_alloc)
		return (NULL);
	new_alloc->ptr = malloc(size);
	if (!new_alloc->ptr)
		return (ft_free((void **)&new_alloc), NULL);
	new_alloc->next = (*gc)->head;
	(*gc)->head = new_alloc;
	return (new_alloc->ptr);
}
