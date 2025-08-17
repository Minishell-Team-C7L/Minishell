/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:56:46 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/18 11:23:23 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

char	*ft_strcpy(char *str_dst, const char *str_src)
{
	size_t	i;

	i = 0;
	while (str_src[i])
	{
		str_dst[i] = str_src[i];
		i++;
	}
	str_dst[i] = '\0';
	return (str_dst);
}
