/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:19 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/19 11:19:44 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

int	msh_env(t_env *env)
{
	t_env	*env_node;

	env_node = env;
	while (env_node)
	{
		if (env_node->value)
			printf("%s=%s\n", env_node->variable, env_node->value);
		env_node = env_node->next;
	}
	return (EXIT_SUCCESS);
}
