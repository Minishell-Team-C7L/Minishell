/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:06:52 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 22:00:57 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"

char	*gc_strdup(const char *str, t_gc **gc)
{
	size_t	str_len;
	char	*dup;

	str_len = ft_strlen(str);
	dup = (char *)gc_malloc(sizeof(char) * (str_len +1), gc);
	if (!dup)
		return (NULL);
	ft_strcpy(dup, str);
	return (dup);
}
