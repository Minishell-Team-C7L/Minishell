/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:12:30 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/19 16:22:39 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

void	env_node_del(t_env **env, const char *variable)
{
	t_env	*env_cur;
	t_env	*env_prev;

	if (!env || !variable)
	{
		dbg_nullarg(__func__);
		return ;
	}
	env_cur = *env;
	env_prev = NULL;
	while (env_cur)
	{
		if (!ft_strcmp(env_cur->variable, variable))
		{
			if (!env_prev)
				*env = env_cur->next;
			else
				env_prev->next = env_cur->next;
			env_node_free(&env_cur);
			return ;
		}
		env_prev = env_cur;
		env_cur = env_cur->next;
	}
}
