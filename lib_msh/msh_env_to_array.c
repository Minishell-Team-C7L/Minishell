/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 09:35:40 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 05:02:33 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

static size_t	static_total_env_with_value(t_env *env_current);
static void		static_fill_ary_env(char **ary_env, t_env **env, t_gc **gc);

char	**msh_env_to_array(t_env **env, t_gc **gc)
{
	char	**ary_env;
	size_t	total_nodes;

	if (!env || !*env || !gc || !*gc)
		return (dbg_nullarg(__func__), NULL);
	total_nodes = static_total_env_with_value(*env);
	ary_env = (char **)msh_null_guard(
			gc_malloc(sizeof(char *) * (total_nodes +1), gc), env, gc);
	static_fill_ary_env(ary_env, env, gc);
	return (ary_env);
}

static size_t	static_total_env_with_value(t_env *env_current)
{
	size_t	total;

	total = 0;
	while (env_current)
	{
		if (env_current->value)
			total++;
		env_current = env_current->next;
	}
	return (total);
}

static void	static_fill_ary_env(char **ary_env, t_env **env, t_gc **gc)
{
	t_env	*env_cur;
	size_t	row;
	char	*tmp_join;

	env_cur = *env;
	row = 0;
	while (env_cur)
	{
		if (env_cur->value)
		{
			tmp_join = (char *)msh_null_guard(
					gc_strjoin(env_cur->variable, "=", gc), env, gc);
			ary_env[row] = (char *)msh_null_guard(
					gc_strjoin(tmp_join, env_cur->value, gc), env, gc);
			row++;
		}
		env_cur = env_cur->next;
	}
	ary_env[row] = NULL;
}
