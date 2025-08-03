/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_path_get_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:11:33 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/03 19:12:26 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

static char	*static_check_path_errors(const char *cmd, t_gc **gc);
static char	*static_get_path_from_dirs(
				const char *cmd, char **ary_dir, t_env **env, t_gc **gc);

char	*msh_path_get_cmd(const char *cmd, t_env **env, t_gc **gc)
{
	t_env	*env_path;
	char	**ary_dir;
	char	*cmd_path;

	if (!cmd || !*cmd || !env || !gc || !*gc)
		return (dbg_nullarg(__func__), NULL);
	if (ft_strchr(cmd, '/'))
		return (static_check_path_errors(cmd, gc));
	env_path = env_get_node(env, "PATH");
	if (!env_path || !env_path->value)
		return (NULL);
	ary_dir = (char **)msh_null_guard(
			gc_split(env_path->value, ':', gc), env, gc);
	cmd_path = static_get_path_from_dirs(cmd, ary_dir, env, gc);
	if (!cmd_path)
	{
		ft_puterr("msh: ");
		ft_puterr(cmd);
		ft_puterr(": command not found\n");
	}
	return (cmd_path);
}

static char	*static_check_path_errors(const char *cmd, t_gc **gc)
{
	struct stat	stat_file;

	if (stat(cmd, &stat_file) == -1)
		return (msh_perror(cmd), NULL);
	if (S_ISDIR(stat_file.st_mode))
	{
		ft_puterr("msh: ");
		ft_puterr(cmd);
		ft_puterr(": is a directory\n");
		errno = EISDIR;
		return (NULL);
	}
	if (access(cmd, X_OK) == -1)
		return (msh_perror(cmd), NULL);
	return (gc_strdup(cmd, gc));
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
