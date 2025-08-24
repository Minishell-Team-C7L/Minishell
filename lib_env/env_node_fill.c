/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 01:58:46 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 22:00:13 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

t_env	*env_node_fill(t_env *env_node, const char *variable, const char *value)
{
	env_node->variable = ft_strdup(variable);
	if (!env_node->variable)
		return (NULL);
	if (value)
	{
		env_node->value = ft_strdup(value);
		if (!env_node->value)
			return (ft_free((void **)&env_node->variable), NULL);
	}
	else
		env_node->value = NULL;
	env_node->next = NULL;
	return (env_node);
}
