/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:19:45 by lhchiban          #+#    #+#             */
/*   Updated: 2024/11/11 14:31:04 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_nbr_words(const char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (s[0] != c && s[0] != '\0')
		n++;
	while (s[i])
	{
		if ((s[i] == c && s[i +1] != c && s[i +1] != '\0'))
			n++;
		i++;
	}
	return (n);
}

static char	*ft_one_word(const char *s, char c, int *i)
{
	int	start;
	int	end;

	while (s[*i] && s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	end = *i;
	return (ft_substr(s, start, end - start));
}

static void	ft_free_splitedstr(char **splitedstr, int j)
{
	while (j > 0)
		free(splitedstr[--j]);
	free(splitedstr);
}

char	**ft_split(char const *s, char c)
{
	char	**splitedstr;
	int		nbrwords;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	nbrwords = ft_nbr_words(s, c);
	splitedstr = (char **) malloc((nbrwords +1) * sizeof(char *));
	if (!splitedstr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < nbrwords)
	{
		splitedstr[j] = ft_one_word(s, c, &i);
		if (!splitedstr[j])
		{
			ft_free_splitedstr(splitedstr, j);
			return (NULL);
		}
		j++;
	}
	splitedstr[j] = NULL;
	return (splitedstr);
}
