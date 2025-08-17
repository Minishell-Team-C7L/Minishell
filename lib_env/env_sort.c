/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:05:29 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/19 17:13:38 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

static void	static_swap_node_data(t_env *node_1, t_env *node_2);

t_env	*env_sort(t_env *env_list)
{
	t_env	*env_cur;
	bool	is_sorted;

	if (!env_list)
		return (NULL);
	is_sorted = false;
	while (is_sorted == false)
	{
		is_sorted = true;
		env_cur = env_list;
		while (env_cur->next)
		{
			if (ft_strcmp(env_cur->variable, env_cur->next->variable) > 0)
			{
				is_sorted = false;
				static_swap_node_data(env_cur, env_cur->next);
			}
			env_cur = env_cur->next;
		}
	}
	return (env_list);
}

static void	static_swap_node_data(t_env *node_1, t_env *node_2)
{
	char	*temp_variable;
	char	*temp_value;

	temp_variable = node_1->variable;
	node_1->variable = node_2->variable;
	node_2->variable = temp_variable;
	temp_value = node_1->value;
	node_1->value = node_2->value;
	node_2->value = temp_value;
}
