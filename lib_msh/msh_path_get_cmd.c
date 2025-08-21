/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_path_get_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:11:33 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 22:09:48 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

static int	static_check_path_errors(
				const char *cmd, char **cmd_path, t_env **env, t_gc **gc);
static char	*static_get_path_from_dirs(
				const char *cmd, char **ary_dir, t_env **env, t_gc **gc);

int	msh_path_get_cmd(const char *cmd, char **cmd_path, t_env **env, t_gc **gc)
{
	t_env	*env_path;
	char	**ary_dir;

	*cmd_path = NULL;
	if (!*cmd)
		return (msh_puterr(NULL, "command not found"), 127);
	if (ft_strchr(cmd, '/'))
		return (static_check_path_errors(cmd, cmd_path, env, gc));
	env_path = env_get_node(env, "PATH");
	if ((!env_path || !env_path->value))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (static_check_path_errors(cmd, cmd_path, env, gc));
		else
			return (msh_puterr(cmd, "No such file or directory"), 127);
	}
	ary_dir = gc_split(env_path->value, ':', gc);
	*cmd_path = static_get_path_from_dirs(cmd, ary_dir, env, gc);
	if (!*cmd_path)
		return (msh_puterr(cmd, "command not found"), 127);
	return (EXIT_SUCCESS);
}

static int	static_check_path_errors(
			const char *cmd, char **cmd_path, t_env **env, t_gc **gc)
{
	struct stat	stat_file;

	if (stat(cmd, &stat_file) == -1)
		return (msh_perror(cmd), 127);
	if (S_ISDIR(stat_file.st_mode))
		return (msh_puterr(cmd, "is a directory"), 127);
	if (access(cmd, X_OK) == -1)
		return (msh_perror(cmd), 127);
	*cmd_path = (char *)msh_null_guard(gc_strdup(cmd, gc), env, gc);
	if (!*cmd_path)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	*static_get_path_from_dirs(
	const char *cmd, char **ary_dir, t_env **env, t_gc **gc)
{
	char	*tmp_path;
	char	*cmd_path;
	size_t	row;

	row = 0;
	while (ary_dir[row])
	{
		tmp_path = (char *)msh_null_guard(
				gc_strjoin(ary_dir[row], "/", gc), env, gc);
		cmd_path = (char *)msh_null_guard(
				gc_strjoin(tmp_path, cmd, gc), env, gc);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		row++;
	}
	return (NULL);
}
