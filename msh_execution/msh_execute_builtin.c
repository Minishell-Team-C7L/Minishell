/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:30:55 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/25 11:31:12 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

int	msh_execute_builtin(t_data *data, int status, t_env **env, t_gc **gc)
{
	const char	**arg;

	arg = (const char **)data->abs->arg;
	if (ft_strcmp(arg[0], "cd") == 0)
		return (msh_cd(arg, &data->last_cwd, env, gc));
	else if (ft_strcmp(arg[0], "echo") == 0)
		return (msh_echo(arg));
	else if (ft_strcmp(arg[0], "env") == 0)
		return (msh_env(*env));
	else if (ft_strcmp(arg[0], "exit") == 0)
		return (msh_exit(data, status));
	else if (ft_strcmp(arg[0], "export") == 0)
		return (msh_export(arg, env, gc));
	else if (ft_strcmp(arg[0], "pwd") == 0)
		return (msh_pwd(data->last_cwd, gc));
	else if (ft_strcmp(arg[0], "unset") == 0)
		return (msh_unset(arg, env));
	return (127);
}
