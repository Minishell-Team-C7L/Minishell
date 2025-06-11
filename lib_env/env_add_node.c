/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:46:58 by aessaber          #+#    #+#             */
/*   Updated: 2025/06/02 17:06:46 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

t_env	*env_add_node(t_env **env, t_gc **gc)
{
	t_env	*env_new;
	t_env	*env_cur;

	if (!env || !gc)
		return (NULL);
	msh_malloc((void **)&env_new, sizeof(t_env), gc);
	env_new->variable = NULL;
	env_new->value = NULL;
	env_new->next = NULL;
	if (!*env)
	{
		*env = env_new;
		return (env_new);
	}
	env_cur = *env;
	while (env_cur->next)
		env_cur = env_cur->next;
	env_cur->next = env_new;
	return (env_new);
}
