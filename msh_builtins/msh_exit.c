/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:28 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/17 05:20:15 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

static int	exit_parse(t_data *data);

int	msh_exit(t_data *data, int status)
{
	if (!data || !data->abs->arg || !*data->abs->arg)
		return (dbg_nullarg(__func__));
	if (!data->abs->arg[1])
	{
		ft_putstr_nl("exit");
		msh_quit(data, status);
	}
	return (exit_parse(data));
}

static int	exit_parse(t_data *data)
{
	uint8_t	status;

	if (!ft_str_is_num(data->abs->arg[1]))
	{
		ft_puterr("msh: exit: ");
		ft_puterr(data->abs->arg[1]);
		ft_puterr(": numeric argument required\n");
		msh_quit(data, UINT8_MAX);
	}
	if (data->abs->arg[2])
		return (ft_puterr("msh: exit: too many arguments\n"), EXIT_FAILURE);
	status = (uint8_t)ft_atoi(data->abs->arg[1]);
	ft_putstr_nl("exit");
	msh_quit(data, status);
	return (EXIT_SUCCESS);
}
