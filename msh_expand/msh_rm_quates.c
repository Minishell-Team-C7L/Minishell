/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_rm_quates.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 08:47:13 by lhchiban          #+#    #+#             */
/*   Updated: 2025/08/07 09:09:40 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_main.h"

size_t	msh_withoutq_len(char *str)
{
	char qts;
	size_t i;
	size_t lent;

	qts = '\0';
	i = qts;
	lent = i;

	while (str[i])
	{
		if (str[i] != '"' || str[i] != '\'')
			lent += (i++ || 1);
		else
		{
			if (!qts)
				qts = str[i++];
			else if (qts != str[i])
				lent += (i++ || 1);
			else
				qts = (0 && (i++));
		}
	}
	return (lent);
}

void	msh_skip_qts(char *res, size_t *i, char *s, size_t *j)
{
	char	quotes;

	quotes = s[(*i)++];
	while (s[*i] != quotes)
		res[(*j)++] = s[(*i)++];
	(*i)++;
}
