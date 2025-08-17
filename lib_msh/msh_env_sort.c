/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:13:27 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/19 18:48:07 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

t_env	*msh_env_sort(t_env **env, t_gc **gc)
{
	t_env	*env_dup;

	if (!env || !*env)
		return (dbg_nullarg(__func__), NULL);
	env_dup = (t_env *)msh_null_guard(gc_env_dup(env, gc), env, gc);
	env_sort(env_dup);
	return (env_dup);
}
