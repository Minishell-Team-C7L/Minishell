/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:32:40 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/07 11:34:29 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"
#include <stdio.h>
t_env	*env_node_update(t_env *env_node, const char *new_value)
{
	char	*old_value;

	if (!env_node)
		return (dbg_nullarg(__func__), NULL);
	old_value = env_node->value;
	env_node->value = ft_strdup(new_value);
	if (!env_node->value)
	{
		env_node->value = old_value;
		return (NULL);
	}
	ft_free((void **)&old_value);
	return (env_node);
}
