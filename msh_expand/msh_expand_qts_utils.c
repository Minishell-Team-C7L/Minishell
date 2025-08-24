/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_qts_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:15:46 by lhchiban          #+#    #+#             */
/*   Updated: 2025/08/24 19:02:56 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

static void	show_quotes(char *value)
{
	int	i;
	i = 0;
	while(value[i])
	{
		if(value[i] == 4)
			value[i] = '"';
		if(value[i] == 3)
			value[i] = '\'';
		i++;
	}
}

void	msh_go_remove_quotes(char **f_expand)
{
	size_t	i;

	i = 0;
	while (f_expand && f_expand[i])
	{
		f_expand[i] = msh_rm_quates(f_expand[i]);
		show_quotes(f_expand[i]);
		i++;
	}
}

void	hide_quotes(char *value)
{
	int	i;

	i = 0;
	while(value[i])
	{
		if(value[i] == '"')
			value[i] = 4;
		if(value[i] == '\'')
			value[i] = 3;
		i++;
	}
}
