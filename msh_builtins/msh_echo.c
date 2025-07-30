/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:01 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/30 10:51:36 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

static void	echo_parse_flag_n(const char **arg, t_echo *echo);
static void	echo_print_args(const char **arg, int row);

int	msh_echo(const char **arg)
{
	t_echo	echo;

	if (!arg || !*arg)
		return (dbg_nullarg(__func__));
	if (!arg[1])
		return (ft_putchar('\n'), EXIT_SUCCESS);
	echo.arg = 1;
	echo.flag_n = false;
	echo_parse_flag_n(arg, &echo);
	echo_print_args(arg, echo.arg);
	if (!echo.flag_n)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}

static void	echo_parse_flag_n(const char **arg, t_echo *echo)
{
	while (arg[echo->arg] && !ft_strncmp(arg[echo->arg], "-n", 2)
		&& ft_str_is_mono(arg[echo->arg], 'n', 1))
	{
		echo->flag_n = true;
		echo->arg++;
	}
}

static void	echo_print_args(const char **arg, int row)
{
	bool	arg_is_not_first;

	arg_is_not_first = false;
	while (arg[row])
	{
		if (arg_is_not_first)
			ft_putchar(' ');
		ft_putstr(arg[row]);
		arg_is_not_first = true;
		row++;
	}
}
