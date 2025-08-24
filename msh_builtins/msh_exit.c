/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:28 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/23 23:18:26 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

static int	exit_parse(t_data *data);

int	msh_exit(t_data *data, int status)
{
	if (!data->abs->arg[1])
	{
		if (!data->is_in_pipe)
			printf("exit\n");
		msh_quit(data, status);
	}
	return (exit_parse(data));
}

static int	exit_parse(t_data *data)
{
	uint8_t	status;

	if (!ft_str_is_num(data->abs->arg[1]))
	{
		msh_puterr("msh: exit: ");
		msh_puterr(data->abs->arg[1]);
		msh_puterr(": numeric argument required\n");
		msh_quit(data, UINT8_MAX);
	}
	if (data->abs->arg[2])
		return (msh_puterr("msh: exit: too many arguments\n"));
	status = (uint8_t)ft_atoi(data->abs->arg[1]);
	if (!data->is_in_pipe)
		printf("exit\n");
	msh_quit(data, status);
	return (EXIT_SUCCESS);
}
