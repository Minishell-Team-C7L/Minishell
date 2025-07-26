/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:38:41 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/21 17:55:41 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

t_env	*env_node_set(
	t_env **env, const char *target_var, const char *new_value)
{
	t_env	*env_node;

	if (!env || !target_var)
		return (dbg_nullarg(__func__), NULL);
	env_node = env_get_node(env, target_var);
	if (env_node)
		return (env_node_update(env_node, new_value));
	else
	{
		env_node = env_node_alloc();
		if (!env_node)
			return (NULL);
		if (!env_node_fill(env_node, target_var, new_value))
			return (env_node_free(&env_node), NULL);
		env_node_add_back(env, env_node);
		return (env_node);
	}
}
