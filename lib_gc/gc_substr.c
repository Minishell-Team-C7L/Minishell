/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:06:52 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 22:01:06 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"

char	*gc_substr(char const *str, unsigned int start, size_t len, t_gc **gc)
{
	char	*sub;
	size_t	s_len;
	size_t	sub_len;

	s_len = ft_strlen(str);
	if (start >= s_len)
		return (gc_strdup("", gc));
	sub_len = s_len - start;
	if (len > sub_len)
		len = sub_len;
	sub = (char *)gc_malloc(sizeof(char) * (len +1), gc);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, str + start, len + 1);
	return (sub);
}
