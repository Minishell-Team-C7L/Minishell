/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:04 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/30 10:51:26 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

static int	cd_change_dir(t_cd *cd, t_env **env, t_gc **gc);
static int	cd_get_path(t_cd *cd, const char **arg, t_env **env);

int	msh_cd(const char **arg, t_env **env, t_gc **gc)
{
	t_cd		cd;

	if (!arg || !*arg || !env || !gc || !*gc)
		return (dbg_nullarg(__func__));
	cd.oldpwd = gc_getcwd(gc);
	if (!cd.oldpwd)
		return (msh_perror("cd"));
	cd.type = CD_ARG;
	if (cd_get_path(&cd, arg, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (cd.type == CD_EMPTY)
		return (EXIT_SUCCESS);
	if (cd_change_dir(&cd, env, gc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (cd.type == CD_OLDPWD)
		ft_putstr_nl(cd.pwd);
	return (EXIT_SUCCESS);
}

static int	cd_change_dir(t_cd *cd, t_env **env, t_gc **gc)
{
	if (chdir(cd->path) == -1)
		return (msh_perror("cd"));
	cd->pwd = gc_getcwd(gc);
	if (!cd->pwd)
		return (msh_perror("cd"));
	msh_null_guard(env_node_set(env, "OLDPWD", cd->oldpwd), env, gc);
	msh_null_guard(env_node_set(env, "PWD", cd->pwd), env, gc);
	return (EXIT_SUCCESS);
}

static int	cd_get_path(t_cd *cd, const char **arg, t_env **env)
{
	if (!arg[1])
	{
		cd->type = CD_HOME;
		cd->env_home = env_get_node(env, "HOME");
		if (!cd->env_home || !cd->env_home->value)
			return (ft_puterr("msh: cd: HOME not set\n"), EXIT_FAILURE);
		cd->path = cd->env_home->value;
		return (EXIT_SUCCESS);
	}
	if (ft_strcmp(arg[1], "-") == 0)
	{
		cd->type = CD_OLDPWD;
		cd->env_oldpwd = env_get_node(env, "OLDPWD");
		if (!cd->env_oldpwd || !cd->env_oldpwd->value)
			return (ft_puterr("msh: cd: OLDPWD not set\n"), EXIT_FAILURE);
		cd->path = cd->env_oldpwd->value;
		return (EXIT_SUCCESS);
	}
	if (!arg[1][0])
		cd->type = CD_EMPTY;
	cd->path = (char *)arg[1];
	return (EXIT_SUCCESS);
}
