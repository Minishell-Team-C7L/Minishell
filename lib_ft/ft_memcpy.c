/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 05:19:42 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 05:21:13 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*mem_dst;
	const char	*mem_src;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	i = 0;
	mem_dst = (char *) dst;
	mem_src = (const char *) src;
	while (i < len)
	{
		(mem_dst[i]) = (mem_src[i]);
		i++;
	}
	return (dst);
}
