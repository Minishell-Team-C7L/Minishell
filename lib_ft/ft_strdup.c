/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:28:16 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/18 11:05:15 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

static size_t	static_strlen(const char *str);
static char		*static_strcpy(char *str_dst, const char *src);

char	*ft_strdup(const char *str)
{
	size_t	str_len;
	char	*str_dup;

	if (!str)
		return (NULL);
	str_len = static_strlen(str);
	str_dup = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str_dup)
		return (NULL);
	static_strcpy(str_dup, str);
	return (str_dup);
}

static size_t	static_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static char	*static_strcpy(char *str_dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		str_dst[i] = src[i];
		i++;
	}
	str_dst[i] = '\0';
	return (str_dst);
}
