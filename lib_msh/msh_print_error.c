/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_print_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:02:05 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/23 23:48:33 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

void	msh_print_error(const char *part1, const char *part2)
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
	printf("%s: ", PROJECT_NAME);
	if (part1)
		printf("%s", part1);
	if (part2)
		printf(": %s", part2);
	printf("\n");
	dup2(fd_stdout, STDOUT_FILENO);
	close(fd_stdout);
}
