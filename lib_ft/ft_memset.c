/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:12:28 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/18 10:27:01 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

void	*ft_memset(void *ptr, int c, size_t len)
{
	unsigned char	*ptr_str;
	size_t			i;

	ptr_str = (unsigned char *)ptr;
	i = 0;
	while (i < len)
	{
		ptr_str[i] = (unsigned char)c;
		i++;
	}
	return (ptr);
}
