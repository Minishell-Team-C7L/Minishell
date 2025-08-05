/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:28 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/30 10:52:03 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

static int	exit_parse(const char **arg, t_env **env, t_gc **gc);

int	msh_exit(const char **arg, int status, t_env **env, t_gc **gc)
{
	if (!arg || !*arg || !env || !gc || !*gc)
		return (dbg_nullarg(__func__));
	if (!arg[1])
	{
		ft_putstr_nl("exit");
		msh_quit(status, env, gc);
	}
	return (exit_parse(arg, env, gc));
}

static int	exit_parse(const char **arg, t_env **env, t_gc **gc)
{
	uint8_t	exit_status;

	if (!ft_str_is_num(arg[1]))
	{
		ft_puterr("msh: exit: ");
		ft_puterr(arg[1]);
		ft_puterr(": numeric argument required\n");
		msh_quit(UINT8_MAX, env, gc);
	}
	if (arg[2])
		return (ft_puterr("msh: exit: too many arguments\n"), EXIT_FAILURE);
	exit_status = (uint8_t)ft_atoi(arg[1]);
	ft_putstr_nl("exit");
	msh_quit(exit_status, env, gc);
	return (EXIT_SUCCESS);
}
