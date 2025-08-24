/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_id_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:30:03 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/23 23:05:29 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

void	msh_id_err(const char *arg, const char *cmd)
{
	int	fd_stdout;

	fd_stdout = dup(STDOUT_FILENO);
	if (fd_stdout == -1)
		return ;
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		close(fd_stdout);
		return ;
	}
	printf("%s: %s: `%s': not a valid identifier\n", PROJECT_NAME, cmd, arg);
	dup2(fd_stdout, STDOUT_FILENO);
	close(fd_stdout);
}
