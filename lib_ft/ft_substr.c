/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:28:28 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/20 16:30:18 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

char	*ft_substr(char const *str, size_t start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	sub_len;

	if (!str)
		return (NULL);
	s_len = ft_strlen(str);
	if (start >= s_len)
		return (ft_strdup(""));
	sub_len = s_len - start;
	if (len > sub_len)
		len = sub_len;
	sub = (char *)malloc(sizeof(char) * (len +1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, str + start, len +1);
	return (sub);
}
