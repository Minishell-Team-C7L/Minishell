/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_create_and_clean.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:04:24 by lhchiban          #+#    #+#             */
/*   Updated: 2025/08/18 09:24:58 by lhchiban         ###   ########.fr       */
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

t_red_node	*msh_new_red_node(char *value, t_token_types t_type)
{
	t_red_node	*red_n_node;

	red_n_node = (t_red_node *)ft_calloc(1, sizeof(t_red_node));
	if (!red_n_node)
		return (NULL);
	red_n_node->val = ft_strdup(value);
	if (!red_n_node->val)
		return (free(red_n_node), NULL);
	red_n_node->heredoc_sign = false;
	if (t_type == HERE_DOC_T && msh_check_heredoc(red_n_node->val))
		red_n_node->heredoc_sign = true;
	red_n_node->type = msh_red_type(t_type);
	return (red_n_node);
}

void	msh_free_cmd_args(t_node *cmd_node)
{
	if (!cmd_node || !cmd_node->args)
		return ;
	free(cmd_node->args);
	cmd_node->args = NULL;
}

void	msh_clear_tree_rec(t_node *tree)
{
	if (!tree)
		return ;
	if (tree->type == CMD_N)
		msh_clear_cmd(tree);
	else
	{
		if (tree -> left)
			msh_clear_tree_rec(tree -> left);
		if (tree -> right)
			msh_clear_tree_rec(tree -> right);
	}
	free(tree);
}
