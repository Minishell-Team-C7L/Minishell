/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_puterr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:13:49 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/23 23:23:05 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

int	msh_puterr(const char *str)
{
	int	fd_stdout;

	fd_stdout = dup(STDOUT_FILENO);
	if (fd_stdout == -1)
		return (EXIT_FAILURE);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		close(fd_stdout);
		return (EXIT_FAILURE);
	}
	if (str)
		printf("%s", str);
	dup2(fd_stdout, STDOUT_FILENO);
	close(fd_stdout);
	return (EXIT_FAILURE);
}
