/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:46:35 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/18 11:21:23 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

int	ft_strcmp(const char *str_1, const char *str_2)
{
	size_t	i;

	i = 0;
	while (str_1[i] || str_2[i])
	{
		if (str_1[i] != str_2[i])
			return ((unsigned char)str_1[i] - (unsigned char)str_2[i]);
		i++;
	}
	return (0);
}
