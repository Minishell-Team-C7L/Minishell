/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:06:52 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/17 19:19:49 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"

char	*gc_strdup(const char *str, t_gc **gc)
{
	size_t	str_len;
	char	*dup;

	if (!str || !gc || !*gc)
		return (dbg_nullarg(__func__), NULL);
	str_len = ft_strlen(str);
	dup = (char *)gc_malloc(sizeof(char) * (str_len +1), gc);
	if (!dup)
		return (NULL);
	ft_strcpy(dup, str);
	return (dup);
}
