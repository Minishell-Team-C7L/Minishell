/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:21:36 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/18 10:38:18 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	col;

	col = 0;
	while (str[col])
	{
		if (str[col] == (char)c)
			return ((char *)str + col);
		col++;
	}
	if (str[col] == (char)c)
		return ((char *)str + col);
	return (NULL);
}
