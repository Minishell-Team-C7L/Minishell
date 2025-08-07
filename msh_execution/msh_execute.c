/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:51:00 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/07 05:03:18 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"
#include "msh_main.h"

int	msh_execute(t_node *ast_head, t_data *data)
{
	if (!ast_head)
		return (data->exit_status);
	// if (msh_handle_heredocs(ast_head) != EXIT_SUCCESS)
	// 	return (EXIT_FAILURE);
	if (ast_head->type == CMD_N)
		return (msh_execute_cmd(
				ast_head, data->exit_status, &data->env, &data->gc));
	else if (ast_head->type == PIPE_N)
		return (msh_execute_pipe(ast_head, data));
	return (EXIT_SUCCESS);
}
