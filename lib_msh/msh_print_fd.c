/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_printf_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 00:05:20 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/24 00:17:41 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

void	msh_print_fd(const char *str, int fd)
{
	int	fd_stdout;

	fd_stdout = dup(STDOUT_FILENO);
	if (fd_stdout == -1)
		return ;
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd_stdout);
		return ;
	}
	printf("%s\n", str);
	dup2(fd_stdout, STDOUT_FILENO);
	close(fd_stdout);
}
