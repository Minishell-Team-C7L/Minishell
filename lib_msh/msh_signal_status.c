/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 08:22:42 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/22 10:55:09 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

int	msh_signal_status(int exit_status)
{
	if (msh_signal() == EXIT_FAILURE)
		return (msh_perror("sigaction"));
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGINT)
			ft_putstr_nl("");
		else if (WTERMSIG(exit_status) == SIGQUIT)
			ft_putstr_nl("Quit: 3");
		return (WTERMSIG(exit_status) + 128);
	}
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
}
