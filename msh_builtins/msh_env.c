/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:19 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/07 13:51:04 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"

int	msh_env(t_env *env)
{
	t_env	*env_node;

	env_node = env;
	while (env_node)
	{
		if (env_node->value)
		{
			ft_putstr(env_node->variable);
			ft_putchar('=');
			ft_putstr_nl(env_node->value);
		}
		env_node = env_node->next;
	}
	return (EXIT_SUCCESS);
}
