/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:36 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/30 10:52:24 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

static int	unset_parse_arg(const char *arg);

int	msh_unset(const char **arg, t_env **env)
{
	int		row;
	uint8_t	exit_status;

	if (!arg || !*arg || !env)
		return (dbg_nullarg(__func__));
	row = 1;
	exit_status = EXIT_SUCCESS;
	while (arg[row])
	{
		if (unset_parse_arg(arg[row]) == EXIT_FAILURE)
			exit_status = EXIT_FAILURE;
		else
			env_node_del(env, arg[row]);
		row++;
	}
	return (exit_status);
}

static int	unset_parse_arg(const char *arg)
{
	int		col;

	col = 0;
	if (!ft_isalpha(arg[col]) && arg[col] != '_')
		return (msh_id_err(arg, "unset"), EXIT_FAILURE);
	while (arg[col] && (ft_isalnum(arg[col]) || arg[col] == '_'))
		col++;
	if (arg[col])
		return (msh_id_err(arg, "unset"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
