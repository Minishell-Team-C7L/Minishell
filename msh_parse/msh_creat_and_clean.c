/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_creat_and_clean.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:04:24 by lhchiban          #+#    #+#             */
/*   Updated: 2025/07/26 11:11:38 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

t_node	*msh_new_node(t_node_type n_type)
{
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = n_type;
	return (new_node);
}

t_node	*msh_new_cmd_node(void)
{
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = CMD_N;
	new_node->args = NULL;
	return (new_node);
}

t_red_node	*msh_new_red_node(t_token_types t_type)
{
	t_red_node	*red_n_node;

	red_n_node = (t_red_node *)ft_calloc(1, sizeof(t_red_node));
	if (!red_n_node)
		return (NULL);
	red_n_node->val = ft_strdup(NULL);
	red_n_node->type = msh_red_type(t_type);
	if (!red_n_node->type)
		return (free(red_n_node), NULL);
	return (red_n_node);
}

void	msh_free_cmd_args(t_node *cmd_node)
{
	if (!cmd_node || !cmd_node->args)
		return ;
	free(cmd_node->args);
	cmd_node->args = NULL;
}

void	msh_free_args_string(char **args)
{
	if (!args || !*args)
		return ;
	free(*args);
	*args = NULL;
}
