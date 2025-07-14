/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:49:05 by lhchiban          #+#    #+#             */
/*   Updated: 2024/10/27 15:49:15 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		i;
	void		*call;

	i = count * size;
	if (count && size && i / size != count)
		return (NULL);
	call = malloc(i);
	if (call == NULL)
		return (call);
	else
		ft_bzero(call, i);
	return (call);
}
