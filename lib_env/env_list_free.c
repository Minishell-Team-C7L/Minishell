/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:58:44 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/25 18:58:55 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

void	env_list_free(t_env **env)
{
	t_env	*env_current;
	t_env	*env_next;

	if (!env)
		return ;
	env_current = *env;
	while (env_current)
	{
		env_next = env_current->next;
		env_node_free(&env_current);
		env_current = env_next;
	}
	*env = NULL;
}
