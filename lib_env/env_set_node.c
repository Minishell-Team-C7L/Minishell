/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:38:41 by aessaber          #+#    #+#             */
/*   Updated: 2025/06/01 06:20:32 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

t_env	*env_set_node(t_env **env, char *target_variable, char *new_value)
{
	t_env	*env_node;
	char	*og_value;

	if (!env || !target_variable || !new_value)
		return (NULL);
	env_node = env_get_node(env, target_variable);
	if (env_node)
	{
		og_value = env_node->value;
		env_node->value = ft_strdup(new_value);
		if (!env_node->value)
		{
			env_node->value = og_value;
			return (ft_puterr("msh: ft_strdup failure\n"), NULL);
		}
		return (free(og_value), env_node);
	}
	env_node = env_add_node(env);
	if (!env_node)
		return (NULL);
	return (env_set_node_all(env_node, target_variable, new_value));
}

int	env_set_node_value(t_env **env, char *target_variable, char *new_value)
{
	t_env	*env_node;

	if (!env || !target_variable || !new_value)
		return (EXIT_FAILURE);
	env_node = env_get_node(env, target_variable);
	if (env_node)
	{
		char *original_value_ptr = env_node->value;
		env_node->value = ft_strdup(new_value);
		if (!env_node->value)
		{
			ft_puterr("msh: env_set_node_value: ft_strdup failure for value update\n");
			env_node->value = original_value_ptr;
			return (EXIT_FAILURE);
		}
		free(original_value_ptr);
		return (EXIT_SUCCESS);
	}
	else
	{
		env_node = env_add_node(env);
		if (!env_node)
		{
			return (EXIT_FAILURE);
		}
		if (env_set_node_all(env_node, target_variable, new_value) == EXIT_FAILURE)
		{
			ft_puterr("msh: env_set_node_value: new_node failure.\n");
			if (*env == env_node)
			{
				*env = env_node->next;
			}
			else
			{
				t_env *scanner = *env;
				while (scanner && scanner->next != env_node)
					scanner = scanner->next;
				if (scanner)
					scanner->next = env_node->next; 
			}
			free(env_node->variable);
			free(env_node->value);
			free(env_node);
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
}
