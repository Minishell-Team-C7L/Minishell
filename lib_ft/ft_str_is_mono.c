/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_mono.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 02:15:39 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/18 10:36:42 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

bool	ft_str_is_mono(const char *str, char constant, size_t start)
{
	if (!str)
		return (false);
	while (str[start])
	{
		if (str[start] != constant)
			return (false);
		start++;
	}
	return (true);
}
