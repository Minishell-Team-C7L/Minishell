/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:36:06 by lhchiban          #+#    #+#             */
/*   Updated: 2025/08/22 18:35:43 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

static size_t	del_dollar_count(char *del)
{
	size_t	i;

	i = 0;
	if (!del)
		return (0);
	while (del[i] == '$')
		i++;
	return (i);
}

char	*msh_heredoc_chval(char *del)
{
	size_t	i;
	size_t	j;
	int		flag;
	char	*res;

	i = 0;
	j = 0;
	flag = 0;
	i = del_dollar_count(del);
	if (i % 2 == 0)
		return (ft_strdup(del));
	res = malloc(sizeof(char) * ft_strlen(del) + 1);
	if (!res)
		return (NULL);
	i = 1;
	while (del[i])
		res[j++] = del[i++];
	res[j] = '\0';
	return (res);
}

bool	msh_dollar_sign(char *delimeter)
{
	size_t	i;

	i = 0;
	while (delimeter[i] && delimeter[i] == '$')
	{
		i++;
		if (delimeter[i] == '"' || delimeter[i] == '\'')
			return (true);
	}
	return (false);
}

bool	msh_is_ambiguous(char *value)
{
	size_t	i;

	i = 0;
	if (!value[i])
		return (true);
	while (value[i] == ' ' || value[i] == '\t')
		i++;
	if (!value[i])
		return (true);
	while (value[i] > 32 && value[i] < 127)
		i++;
	while (value[i] == ' ' || value[i] == '\t')
		i++;
	if (value[i])
		return (true);
	return (false);
}
