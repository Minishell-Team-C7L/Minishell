/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:38:41 by aessaber          #+#    #+#             */
/*   Updated: 2025/05/26 23:33:20 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

t_env	*env_get_node(t_env **env, char *target_variable)
{
	t_env	*env_cur;

	if (!env || !*env || !target_variable)
		return (NULL);
	env_cur = *env;
	while (env_cur)
	{
		if (env_cur->variable && !ft_strcmp(env_cur->variable, target_variable))
			return (env_cur);
		env_cur = env_cur->next;
	}
	return (NULL);
}
