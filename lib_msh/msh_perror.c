/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_perror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:58:31 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/23 22:41:47 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

int	msh_perror(const char *cmd_name)
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
	printf("%s: %s: %s\n", PROJECT_NAME, strerror(errno), cmd_name);
	dup2(fd_stdout, STDOUT_FILENO);
	close(fd_stdout);
	return (EXIT_FAILURE);
}
