/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 08:22:42 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/23 23:57:41 by aessaber         ###   ########.fr       */
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
			printf("^C\n");
		else if (WTERMSIG(exit_status) == SIGQUIT)
			printf("^\\Quit: 3\n");
		return (WTERMSIG(exit_status) + 128);
	}
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
}
