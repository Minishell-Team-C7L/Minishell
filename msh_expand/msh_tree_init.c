/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tree_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:44:16 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/30 05:45:49 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

static void	static_set_up_exp_args(t_node *tree_node, t_data *data);

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
		static_set_up_exp_args(tree_node, data);
}

static void	static_set_up_exp_args(t_node *tree_node, t_data *data)
{
	int	j;

	if (tree_node->args)
		tree_node->node_args = msh_handel_expand(tree_node->args, data);
	j = 0;
	while (tree_node->node_args[j++]);
		// printf("%s\n", tree_node->node_args[j++]);
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