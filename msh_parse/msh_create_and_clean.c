/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_create_and_clean.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:04:24 by lhchiban          #+#    #+#             */
/*   Updated: 2025/08/22 01:34:02 by lhchiban         ###   ########.fr       */
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

t_red_node	*msh_new_red_node(char *value, t_token_types t_type, t_data *data)
{
	t_red_node	*red_n_node;

	red_n_node = (t_red_node *)ft_calloc(1, sizeof(t_red_node));
	if (!red_n_node)
		return (NULL);
	if (t_type != HERE_DOC_T)
	{
		value = msh_handel_expand(value, data);
		if (!value)
			return(red_n_node->is_ambiguous = true, NULL);
		red_n_node->val = msh_rm_quates(value);
	}
	if (!red_n_node->val && t_type != HERE_DOC_T)
		return (free(red_n_node), NULL);
	if (t_type == HERE_DOC_T && msh_check_heredoc(value))
		red_n_node->heredoc_sign = true;
	if (t_type == HERE_DOC_T && msh_dollar_sign(value))
		red_n_node->val = msh_heredoc_chval(value);
	else if (t_type == HERE_DOC_T)
		red_n_node->val = ft_strdup(value);
	if (!red_n_node->val)
		return (free(red_n_node), NULL);
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

void	msh_clear_tree_rec(t_node *tree, t_data *data)
{
	if (!tree)
		return ;
	if (tree->type == CMD_N)
		msh_clear_cmd(tree, data);
	else
	{
		if (tree -> left)
			msh_clear_tree_rec(tree -> left, data);
		if (tree -> right)
			msh_clear_tree_rec(tree -> right, data);
	}
	free(tree);
}
