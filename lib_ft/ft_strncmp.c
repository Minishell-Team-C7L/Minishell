/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:53:59 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/18 11:14:41 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

int	ft_strncmp(const char *str_1, const char *str_2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && (str_1[i] || str_2[i]))
	{
		if (str_1[i] != str_2[i])
			return ((unsigned char)str_1[i] - (unsigned char)str_2[i]);
		i++;
	}
	return (0);
}
