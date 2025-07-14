/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:14:07 by lhchiban          #+#    #+#             */
/*   Updated: 2024/11/11 20:29:01 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned	int, char))
{
	char	*holder;
	int		i;

	if (!s || !f)
		return (NULL);
	i = 0;
	holder = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!holder)
		return (NULL);
	while (s[i])
	{
		holder[i] = f(i, s[i]);
		i++;
	}
	holder[i] = '\0';
	return (holder);
}
