/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_node_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 01:58:46 by aessaber          #+#    #+#             */
/*   Updated: 2025/06/01 04:23:32 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

t_env	*env_set_node_all(t_env *env_node, char *variable, char *value)
{
	if (!env_node || !variable || !value)
		return (NULL);
	env_node->variable = ft_strdup(variable);
	env_node->value = ft_strdup(value);
	env_node->next = NULL;
	if (!env_node->variable || !env_node->value)
	{
		ft_puterr("msh: env_add_node: ft_strdup failure\n");
		free(env_node->variable);
		free(env_node->value);
		//either add a prev to t_env, or do a while loop till you find the ->next that leads to "env_node"
		return (NULL);
	}
	return (env_node);
}
