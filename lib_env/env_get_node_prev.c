/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_node_prev.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:38:41 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 21:59:36 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

t_env	*env_get_node_prev(t_env **env, const char *target_variable)
{
	t_env	*env_current;

	env_current = *env;
	while (env_current && env_current->next)
	{
		if (!ft_strcmp(env_current->next->variable, target_variable))
			return (env_current);
		env_current = env_current->next;
	}
	return (NULL);
}
