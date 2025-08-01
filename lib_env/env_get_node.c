/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:38:41 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/17 20:56:12 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

t_env	*env_get_node(t_env **env, const char *target_variable)
{
	t_env	*env_current;

	if (!env || !target_variable)
		return (dbg_nullarg(__func__), NULL);
	env_current = *env;
	while (env_current)
	{
		if (!ft_strcmp(env_current->variable, target_variable))
			return (env_current);
		env_current = env_current->next;
	}
	return (NULL);
}
