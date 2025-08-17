/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_add_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:27:05 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/19 10:27:13 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

void	env_node_add_back(t_env **env, t_env *new_node)
{
	t_env	*env_current;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	env_current = *env;
	while (env_current->next)
		env_current = env_current->next;
	env_current->next = new_node;
}
