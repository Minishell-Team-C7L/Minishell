/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 23:37:04 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/24 23:42:18 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

void	*static_bzero(void *ptr, size_t len);

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	bytes;
	void	*mem;

	bytes = nmemb * size;
	if (nmemb && bytes / nmemb != size)
		return (NULL);
	mem = malloc(bytes);
	if (!mem)
		return (NULL);
	static_bzero(mem, bytes);
	return (mem);
}

void	*static_bzero(void *ptr, size_t len)
{
	unsigned char	*ptr_str;
	size_t			i;

	ptr_str = (unsigned char *)ptr;
	i = 0;
	while (i < len)
	{
		ptr_str[i] = (unsigned char)0;
		i++;
	}
	return (ptr);
}
