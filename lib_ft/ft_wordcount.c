/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:19:00 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/18 17:19:29 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

size_t	ft_wordcount(const char *str, char delimiter)
{
	size_t	col;
	size_t	word_count;

	if (!str)
		return (0);
	col = 0;
	word_count = 0;
	while (str[col])
	{
		while (str[col] && str[col] == delimiter)
			col++;
		if (str[col])
		{
			word_count++;
			while (str[col] && str[col] != delimiter)
				col++;
		}
	}
	return (word_count);
}
