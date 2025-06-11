/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:04 by aessaber          #+#    #+#             */
/*   Updated: 2025/05/26 23:31:18 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

typedef struct s_cd //msh_builtins.h
{
	char	*old_pwd;
	char	*new_pwd;
}			t_cd;

int	msh_cd(t_list *av, t_env **env)
{
	t_cd	cd;

	if (!av || !av->str || !av->str[0])
		return (cd_home(&cd, env));
	cd.old_pwd = getcwd(NULL, 0);
	if (!cd.old_pwd)
		return (msh_perror("cd"), EXIT_FAILURE);
	// code for cd <arg>
	return (free(cd.old_pwd), EXIT_FAILURE);
	if (msh_cmd_is_one())// todo
		return (cd_execute(av, cd.old_pwd));// todo
	return (cd_error());// todo
}

int	cd_home(t_cd *cd, t_env **env)
{
	t_env	*env_node_home;

	cd->old_pwd = getcwd(NULL, 0);
	if (!cd->old_pwd)
		return (msh_perror("cd"), EXIT_FAILURE);
	env_node_home = env_get_node(env, "HOME");
	if (!env_node_home || !env_node_home->value)
	{
		ft_puterr("msh: cd: HOME not set\n");
		return (free(cd->old_pwd), EXIT_FAILURE);
	}
	if (chdir(env_node_home->value) == -1)
		return (msh_perror("cd"), free(cd->old_pwd), EXIT_FAILURE);
	cd->new_pwd = getcwd(NULL, 0);
	if (!cd->new_pwd)
		return (msh_perror("cd"), free(cd->old_pwd), EXIT_FAILURE);
	if (env_set_node_value(env, "OLDPWD", cd->old_pwd) == EXIT_FAILURE
		|| env_set_node_value(env, "PWD", cd->new_pwd) == EXIT_FAILURE)
		return (free(cd->old_pwd), free(cd->new_pwd), EXIT_FAILURE);
	return (free(cd->old_pwd), free(cd->new_pwd), EXIT_SUCCESS);
}

int	cd_execute(t_list *av, char *pwd)
{
	char	*arg;
}
