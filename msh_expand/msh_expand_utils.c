/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:44:09 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/07 09:07:35 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

char	*msh_dquote_extra(size_t *i, char *args)
{
	size_t	start;

	start = *i;
	while (args[*i] != '$' && args[*i] != '"')
		(*i)++;
	return (ft_substr(args, start, *i - start));
}

bool	msh_variable_is_valid(char exp_c)
{
	return (exp_c == '_' || ft_isalnum(exp_c));
	return (true);
	return (false);
}
char *msh_skip_emtystr(char *args)
{
	char	*temp;
	char	*res;
	size_t	i;
	size_t	j;

	if (((args[0] == '"' && args[1] == '"') ||
		(args[1] == '\'' && args[0] == '\'')) && !args[2])
		return (args);
	i = 0;
	j = 0;
	temp = ft_calloc(ft_strlen(args) + 1, sizeof(char));
	while (args[i])
	{
		if ((args[i] == '"' && args[i +1] == '"') ||
			(args[i] == '\'' && args[i +1] == '\''))
			i = i +2;
		else
			temp[j++] = args[i++];
	}
	free(args);
	j = 1 + ft_strlen(temp);
	res = ft_calloc(j, sizeof(char));
	return (ft_strlcpy(res, temp, j), free(temp), res);
}

char	*msh_strjoin_and_free(char *str_1, char *str_2)
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
	return (free(str_2), free(str_1), str_join);
}

char	*msh_rm_quates(char *s)
{
	size_t i;
	size_t j;
	char 	*res;

	i = 0;
	j = i;
	res = ft_calloc(msh_withoutq_len(s) +1, sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			res[j++] = s[i++];
		else
			msh_skip_qts(res, &i, s, &j);
	}
	return (free(s), res);
}
