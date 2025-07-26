/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:32:22 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/19 15:34:23 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

char	*ft_strjoin(char const *str_1, char const *str_2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str_join;

	if (!str_1 && !str_2)
		return (NULL);
	if (!str_1)
		return (ft_strdup(str_2));
	if (!str_2)
		return (ft_strdup(str_1));
	s1_len = ft_strlen(str_1);
	s2_len = ft_strlen(str_2);
	str_join = (char *)malloc(sizeof(char) * (s1_len + s2_len +1));
	if (!str_join)
		return (NULL);
	ft_strcpy(str_join, str_1);
	ft_strcpy(str_join + s1_len, str_2);
	return (str_join);
}
