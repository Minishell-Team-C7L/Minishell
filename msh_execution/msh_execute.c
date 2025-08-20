/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:51:00 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/19 09:46:36 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

int	msh_execute(t_data *data, t_node *ast_head)
{
	if (!ast_head)
		return (data->exit_status);
	if (ast_head->type == CMD_N)
	{
		data->abs = ast_head;
		return (msh_execute_cmd(
				data, data->exit_status, &data->env, &data->gc));
	}
	else if (ast_head->type == PIPE_N)
		return (msh_execute_pipe(ast_head, data));
	return (EXIT_SUCCESS);
}
