/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:20:50 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/10 04:23:19 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"

void	*gc_calloc(size_t count, size_t size, t_gc **gc)
{
	void	*ptr;

	if (!gc || !*gc)
		return (dbg_nullarg(__func__), NULL);
	ptr = gc_malloc(count * size, gc);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
