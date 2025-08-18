/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:03:23 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/18 19:48:20 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"
#include <stdio.h>
static char	**static_array_fill(
				char **array,
				const char *str,
				char delimiter,
				t_gc **gc
				);

char	**gc_split(const char *str, char delimiter, t_gc **gc)
{
	char	**array;
	size_t	word_count;

	if (!str || !gc || !*gc)
		return (NULL);
	word_count = ft_wordcount(str, delimiter);
	array = (char **)gc_malloc(sizeof(char *) * (word_count +1), gc);
	if (!array)
		return (NULL);
	return (static_array_fill(array, str, delimiter, gc));
}

static char	**static_array_fill(
	char **array,
	const char *str,
	char delimiter,
	t_gc **gc
)
{
	size_t	col;
	size_t	row;
	size_t	word_start;

	col = 0;
	row = 0;
	while (str[col])
	{
		while (str[col] && str[col] == delimiter)
			col++;
		if (str[col])
		{
			word_start = col;
			while (str[col] && str[col] != delimiter)
				col++;
			array[row] = gc_substr(str, word_start, col - word_start, gc);
			if (!array[row])
				return (NULL);
			row++;
		}
	}
	array[row] = NULL;
	return (array);
}
