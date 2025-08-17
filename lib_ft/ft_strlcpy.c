/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 06:36:22 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/18 11:04:43 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

static size_t	static_strlen(const char *str);

size_t	ft_strlcpy(char *str_dst, const char *str_src, size_t size_dst)
{
	size_t	col;

	if (!size_dst)
		return (static_strlen(str_src));
	col = 0;
	while (str_src[col] && col < size_dst - 1)
	{
		str_dst[col] = str_src[col];
		col++;
	}
	str_dst[col] = '\0';
	return (static_strlen(str_src));
}

static size_t	static_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
