/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:26:10 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/01 11:24:58 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

#define FORK_FAILURE -1
#define FORK_SUCCESS 0

static bool	static_is_builtin_parent(const char *cmd);
static int	static_execute_builtin(
				const char **arg, int status, t_env **env, t_gc **gc);
static void	static_execute_child(
				t_node *node, int status, t_env **env, t_gc **gc);
static int	static_execute_external(const char **arg, t_env **env, t_gc **gc);

int	msh_execute_cmd(t_node *node, int status, t_env **env, t_gc **gc)
{
	pid_t	pid;
	int		exit_status;

	if (!node || !node->arg || !node->arg[0] || !env || !gc || !*gc)
		return (dbg_nullarg(__func__), EXIT_SUCCESS);
	if (static_is_builtin_parent(node->arg[0]))
		return (static_execute_builtin(
				(const char **)node->arg, status, env, gc));
	pid = fork();
	if (pid == FORK_FAILURE)
		return (msh_perror("fork"));
	if (pid == FORK_SUCCESS)
		static_execute_child(node, status, env, gc);
	if (waitpid(pid, &exit_status, 0) == -1)
		return (msh_perror("waitpid"));
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
	const char **arg, int status, t_env **env, t_gc **gc)
{
	if (!arg || !arg[0] || !env || !gc || !*gc)
		return (dbg_nullarg(__func__));
	if (ft_strcmp(arg[0], "cd") == 0)
		return (msh_cd(arg, env, gc));
	else if (ft_strcmp(arg[0], "echo") == 0)
		return (msh_echo(arg));
	else if (ft_strcmp(arg[0], "env") == 0)
		return (msh_env(*env));
	else if (ft_strcmp(arg[0], "exit") == 0)
		return (msh_exit(arg, status, env, gc));
	else if (ft_strcmp(arg[0], "export") == 0)
		return (msh_export(arg, env, gc));
	else if (ft_strcmp(arg[0], "pwd") == 0)
		return (msh_pwd(gc));
	else if (ft_strcmp(arg[0], "unset") == 0)
		return (msh_unset(arg, env));
	return (CMD_NOT_FOUND);
}

static void	static_execute_child(
	t_node *node, int status, t_env **env, t_gc **gc)
{
	int		exit_status;

	msh_redir_handle(node->red_l);
	exit_status = static_execute_builtin(
			(const char **)node->arg, status, env, gc);
	if (exit_status != CMD_NOT_FOUND)
		msh_quit(exit_status, env, gc);
	exit_status = static_execute_external((const char **)node->arg, env, gc);
	msh_quit(exit_status, env, gc);
}

static int	static_execute_external(const char **arg, t_env **env, t_gc **gc)
{
	char	*path_cmd;
	char	**envp;

	path_cmd = msh_path_get_cmd(arg[0], env, gc);
	if (!path_cmd)
	{
		ft_puterr("msh: ");
		ft_puterr(arg[0]);
		ft_puterr(": command not found\n");
		return (CMD_NOT_FOUND);
	}
	envp = msh_env_to_array(env, gc);
	if (execve(path_cmd, (char *const *)arg, envp) == -1)
		return (msh_perror(arg[0]));
	return (EXIT_FAILURE);
}
