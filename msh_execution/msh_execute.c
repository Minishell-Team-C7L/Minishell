/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:51:00 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/22 09:26:38 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

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
		exit_status = msh_execute_cmd(
				data, data->exit_status, &data->env, &data->gc);
	}
	else if (ast_head->type == PIPE_N)
		exit_status = msh_execute_pipe(ast_head, data);
	else
		exit_status = EXIT_SUCCESS;
	ft_lstclear(&data->child_pids, free);
	return (exit_status);
}
