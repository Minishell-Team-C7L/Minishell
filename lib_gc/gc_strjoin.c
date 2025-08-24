/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:26:26 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 22:01:02 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"

char	*gc_strjoin(char const *str_1, char const *str_2, t_gc **gc)
{
	size_t	str_1_len;
	size_t	str_2_len;
	char	*str_joined;

	if (!str_1 && !str_2)
		return (gc_strdup("", gc));
	if (!str_1)
		return (gc_strdup(str_2, gc));
	if (!str_2)
		return (gc_strdup(str_1, gc));
	str_1_len = ft_strlen(str_1);
	str_2_len = ft_strlen(str_2);
	str_joined = (char *)gc_malloc(sizeof(char) * (str_1_len + str_2_len +1),
			gc);
	if (!str_joined)
		return (NULL);
	ft_strcpy(str_joined, str_1);
	ft_strcpy(str_joined + str_1_len, str_2);
	return (str_joined);
}
