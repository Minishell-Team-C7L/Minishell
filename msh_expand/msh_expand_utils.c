/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:44:09 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/25 16:01:33 by aessaber         ###   ########.fr       */
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
