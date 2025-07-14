/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:45:01 by lhchiban          #+#    #+#             */
/*   Updated: 2024/11/16 13:20:25 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	find_p(const char *s, char c)
{
	int	k;

	k = 0;
	while (s[k])
	{
		if (c == s[k])
			return (1);
		k++;
	}
	return (0);
}

char	*ft_strtrim(char const	*s1, char const	*set)
{
	char	*str1;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1);
	if (i == j)
		return (ft_strdup(""));
	while (i < j && find_p(set, s1[i]))
		i++;
	while (find_p(set, s1[j - 1]) && j > i)
		j--;
	str1 = ft_substr(s1, i, j - i);
	return (str1);
}
