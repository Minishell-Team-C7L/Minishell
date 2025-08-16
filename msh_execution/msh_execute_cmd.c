/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:26:10 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/16 18:38:41 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

static bool	static_is_builtin_parent(const char *cmd);
static int	static_execute_builtin(
				t_data *data, int status, t_env **env, t_gc **gc);
static void	static_execute_child(
				t_data *data, int status, t_env **env, t_gc **gc);
static int	static_execute_external(const char **arg, t_env **env, t_gc **gc);

int	msh_execute_cmd(t_data *data, int status, t_env **env, t_gc **gc)
{
	pid_t	pid;
	int		exit_status;

	if (!data || !env || !gc || !*gc)
		return (dbg_nullarg(__func__), EXIT_SUCCESS);
	if (static_is_builtin_parent(data->abs->arg[0]))
		return (static_execute_builtin(data, status, env, gc));
	if (msh_signal_off() == EXIT_FAILURE)
		return (msh_perror("sigaction"));
	pid = fork();
	if (pid == FORK_FAILURE)
		return (msh_perror("fork"));
	if (pid == FORK_SUCCESS)
		static_execute_child(data, status, env, gc);
	if (waitpid(pid, &exit_status, 0) == -1)
		return (msh_perror("waitpid"));
	if (msh_signal() == EXIT_FAILURE)
		return (msh_perror("sigaction"));
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
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

static int	static_execute_builtin(
	t_data *data, int status, t_env **env, t_gc **gc)
{
	const char	**arg;

	if (!data->abs->arg || !data->abs->arg[0] || !env || !gc || !*gc)
		return (dbg_nullarg(__func__));
	arg = (const char **)data->abs->arg;
	if (ft_strcmp(arg[0], "cd") == 0)
		return (msh_cd(arg, env, gc));
	else if (ft_strcmp(arg[0], "echo") == 0)
		return (msh_echo(arg));
	else if (ft_strcmp(arg[0], "env") == 0)
		return (msh_env(*env));
	else if (ft_strcmp(arg[0], "exit") == 0)
		return (msh_exit(data, status));
	else if (ft_strcmp(arg[0], "export") == 0)
		return (msh_export(arg, env, gc));
	else if (ft_strcmp(arg[0], "pwd") == 0)
		return (msh_pwd(gc));
	else if (ft_strcmp(arg[0], "unset") == 0)
		return (msh_unset(arg, env));
	return (127);
}

static void	static_execute_child(
	t_data *data, int status, t_env **env, t_gc **gc)
{
	int					exit_status;

	if (msh_signal_child() == EXIT_FAILURE)
		exit(msh_perror("sigaction"));
	msh_handle_redir(data->abs->red_l);
	exit_status = static_execute_builtin(data, status, env, gc);
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

	if (!ft_strcmp(arg[0], ".")
		|| !ft_strcmp(arg[0], ".."))
		return (msh_puterr(arg[0], "command not found"), 127);
	exit_status = msh_path_get_cmd(arg[0], &cmd_path, env, gc);
	if (exit_status)
		return (exit_status);
	envp = msh_env_to_array(env, gc);
	if (execve(cmd_path, (char *const *)arg, envp) == -1)
		return (msh_perror(arg[0]));
	return (EXIT_FAILURE);
}
