/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_env_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 08:49:35 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 22:00:42 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gc.h"

static t_env	*static_gc_dup_node(const t_env *src_node, t_gc **gc);

t_env	*gc_env_dup(t_env **env, t_gc **gc)
{
	t_env	*env_cur;
	t_env	*dup_node;
	t_env	*dup_head;
	t_env	*dup_last;

	env_cur = *env;
	dup_head = NULL;
	dup_last = NULL;
	while (env_cur)
	{
		dup_node = static_gc_dup_node(env_cur, gc);
		if (!dup_node)
			return (NULL);
		if (!dup_head)
			dup_head = dup_node;
		else
			dup_last->next = dup_node;
		dup_last = dup_node;
		env_cur = env_cur->next;
	}
	return (dup_head);
}

static t_env	*static_gc_dup_node(const t_env *src_node, t_gc **gc)
{
	t_env	*new_node;

	new_node = gc_malloc(sizeof(t_env), gc);
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_env));
	new_node->variable = gc_strdup(src_node->variable, gc);
	if (!new_node->variable)
		return (NULL);
	if (src_node->value)
	{
		new_node->value = gc_strdup(src_node->value, gc);
		if (!new_node->value)
			return (NULL);
	}
	return (new_node);
}
