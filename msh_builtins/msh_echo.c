/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:01 by aessaber          #+#    #+#             */
/*   Updated: 2025/05/17 20:07:36 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

int	msh_echo(t_list *av)
{
	t_echo	echo;

	if (!av || !av->str)
		return (ft_putchar('\n'), EXIT_SUCCESS);
	echo.flag_n = false;
	while (av && av->str
		&& !ft_strncmp(av->str, "-n", 2)
		&& ft_str_is_mono(av->str, 'n', 1))
	{
		echo.flag_n = true;
		av = av->next;
	}
	echo.is_not_first = false;
	while (av)
	{
		if (echo.is_not_first)
			ft_putchar(' ');
		if (av->str)
			ft_putstr(av->str);
		echo.is_not_first = true;
		av = av->next;
	}
	if (!echo.flag_n)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}
