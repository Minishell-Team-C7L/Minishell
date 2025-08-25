/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:26:10 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/25 11:59:59 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

static int	msh_execute_special_case(
				t_data *data, int status, t_env **env, t_gc **gc);
static bool	static_is_builtin_parent(const char *cmd);
static void	static_execute_child(
				t_data *data, int status, t_env **env, t_gc **gc);
static int	static_execute_external(const char **arg, t_env **env, t_gc **gc);

int	msh_execute_cmd(t_data *data, int status, t_env **env, t_gc **gc)
{
	pid_t	pid;
	int		exit_status;

	exit_status = msh_execute_special_case(data, status, env, gc);
	if (exit_status != NOT_A_SPECIAL_CASE)
		return (exit_status);
	if (msh_signal_off() == EXIT_FAILURE)
		return (msh_perror("sigaction"));
	pid = fork();
	if (pid == FORK_FAILURE)
		return (msh_perror("fork"));
	if (pid == IS_CHILD)
		static_execute_child(data, status, env, gc);
	if (waitpid(pid, &exit_status, 0) == -1)
		return (msh_perror("waitpid"));
	return (msh_signal_status(exit_status));
}

static int	msh_execute_special_case(
	t_data *data, int status, t_env **env, t_gc **gc)
{
	if (data->abs->arg && data->abs->arg[0])
	{
		if (static_is_builtin_parent(data->abs->arg[0]))
		{
			if (msh_handle_redir(data->abs->red_l, false) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			return (msh_execute_builtin(data, status, env, gc));
		}
	}
	if (data->is_onlyqts)
	{
		data->is_onlyqts = false;
		if (msh_handle_redir(data->abs->red_l, false) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (msh_print_error("command not found", NULL), 127);
	}
	return (NOT_A_SPECIAL_CASE);
}

static bool	static_is_builtin_parent(const char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (true);
	return (false);
}

static void	static_execute_child(
	t_data *data, int status, t_env **env, t_gc **gc)
{
	int					exit_status;

	if (msh_signal_child() == EXIT_FAILURE)
		exit(msh_perror("sigaction"));
	msh_handle_redir(data->abs->red_l, true);
	if (!data->abs->arg || !data->abs->arg[0])
		msh_quit(data, EXIT_SUCCESS);
	exit_status = msh_execute_builtin(data, status, env, gc);
	if (exit_status != 127)
		msh_quit(data, exit_status);
	exit_status = static_execute_external(
			(const char **)data->abs->arg, env, gc);
	msh_quit(data, exit_status);
}

static int	static_execute_external(const char **arg, t_env **env, t_gc **gc)
{
	char	*cmd_path;
	int		exit_status;
	char	**envp;
	t_env	*env_path;

	env_path = env_get_node(env, "PATH");
	if (!ft_strcmp(arg[0], ".")
		|| (!ft_strcmp(arg[0], "..")
			&& env_path
			&& env_path->value
			&& *env_path->value != 0))
		return (msh_print_error(arg[0], "command not found"), 127);
	exit_status = msh_path_get_cmd(arg[0], &cmd_path, env, gc);
	if (exit_status)
		return (exit_status);
	envp = msh_env_to_array(env, gc);
	if (execve(cmd_path, (char *const *)arg, envp) == -1)
		return (msh_perror(arg[0]));
	return (EXIT_FAILURE);
}
