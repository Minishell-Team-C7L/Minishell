/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:49:05 by lhchiban          #+#    #+#             */
/*   Updated: 2024/10/27 15:49:08 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t	n)
{
	const unsigned char	*str;
	size_t				i;
	unsigned char		c1;

	str = (const unsigned char *)s;
	i = 0;
	c1 = (unsigned char)c;
	while (i < n)
	{
		if (c1 == str[i])
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
