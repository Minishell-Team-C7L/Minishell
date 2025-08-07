/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tree_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:44:16 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/07 11:50:05 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

static char	**static_set_up_exp_args(char *str, t_node *tree_node, t_data *data);

void	msh_tree_init(t_node *tree_node, t_data *data)
{
	if (!tree_node)
		return ;
	if (tree_node->type == PIPE_N)
	{
		msh_tree_init(tree_node->left, data);
		msh_tree_init(tree_node->right, data);
	}
	else
	{
		if (tree_node->args)
			tree_node->arg = static_set_up_exp_args(tree_node->args, tree_node, data);
	}
}

static char	**static_set_up_exp_args(char *str, t_node *tree_node, t_data *data)
{
	size_t	i;
	char **f_expand;

	(void)tree_node;
	str = msh_handel_expand(str, data);
	if (!str)
		return (NULL);
	str = msh_skip_emtystr(str);
	if (!str)
		return (NULL);
	f_expand = msh_expand_split_args(str);
	free(str);
	if (!f_expand)
		return (NULL);
	i = -1;
	while (f_expand[++i])
		f_expand[i] = msh_rm_quates(f_expand[i]);
	return (f_expand);
}

// static bool msh_check_signals(int signal_state)
// {
//     if (signal_state)
//     {
//         // Handle heredoc signal logic here
//         // For example, you might want to set up a heredoc file descriptor
//         return true; // Continue processing the right branch
//     }
//     return false; // Skip processing the right branch if no heredoc signal
// }
