/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:51:00 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/24 20:09:27 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

static void	static_restore_std_fds(int stdin_backup, int stdout_backup);

int	msh_execute(t_data *data, t_node *ast_head)
{
	char	*last_cwd;
	int		exit_status;

	last_cwd = gc_getcwd(&data->gc);
	if (last_cwd)
		data->last_cwd = last_cwd;
	if (!ast_head)
		return (data->exit_status);
	data->child_pids = NULL;
	if (ast_head->type == CMD_N)
	{
		data->abs = ast_head;
		data->stdin_backup = dup(STDIN_FILENO);
		data->stdout_backup = dup(STDOUT_FILENO);
		exit_status = msh_execute_cmd(
				data, data->exit_status, &data->env, &data->gc);
		static_restore_std_fds(data->stdin_backup, data->stdout_backup);
	}
	else if (ast_head->type == PIPE_N)
		exit_status = msh_execute_pipe(ast_head, data);
	else
		exit_status = EXIT_SUCCESS;
	ft_lstclear(&data->child_pids, free);
	return (exit_status);
}

static void	static_restore_std_fds(int stdin_backup, int stdout_backup)
{
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
		exit(msh_perror("stdin"));
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		exit(msh_perror("stdout"));
	close(stdin_backup);
	close(stdout_backup);
}
