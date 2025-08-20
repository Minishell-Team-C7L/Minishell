/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_defaults.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:47:12 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 05:51:47 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

void	msh_env_defaults(t_env **env, t_gc **gc)
{
	t_env	*env_shlvl;
	int		shlvl_value;
	char	*shlvl_str;

	env_node_set(env, "OLDPWD", NULL);
	if (!env_get_node(env, "PATH"))
		env_node_set(env, "PATH",
			"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env_node_set(env, "PWD", gc_getcwd(gc));
	env_shlvl = env_get_node(env, "SHLVL");
	if (!env_shlvl)
		env_node_set(env, "SHLVL", "1");
	else
	{
		shlvl_value = ft_atoi(env_shlvl->value);
		if (shlvl_value < 0)
			shlvl_value = 0;
		else
			shlvl_value++;
		shlvl_str = ft_itoa(shlvl_value);
		env_node_set(env, "SHLVL", shlvl_str);
		ft_free((void **)&shlvl_str);
	}
}
