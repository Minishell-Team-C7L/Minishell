/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:20:14 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/10 03:18:30 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"

void	gc_free(t_gc **gc)
{
	t_alloc	*alloc_current;
	t_alloc	*alloc_next;

	if (!gc || !*gc)
		return ;
	alloc_current = (*gc)->head;
	while (alloc_current)
	{
		alloc_next = alloc_current->next;
		ft_free((void **)&alloc_current->ptr);
		ft_free((void **)&alloc_current);
		alloc_current = alloc_next;
	}
	ft_free((void **)gc);
}
