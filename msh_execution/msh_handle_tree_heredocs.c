/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_tree_heredocs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:31:46 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 22:32:49 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

void	msh_handle_tree_heredocs(t_data *data, t_node *node)
{
	if (!node)
		return ;
	if (data->heredoc_count > 16)
		msh_quit(data, 2);
	if (node->type == CMD_N)
	{
		if (msh_handle_heredocs(data, node) != EXIT_SUCCESS)
		{
			data->hd_err = true;
			data->exit_status = EXIT_FAILURE;
			return ;
		}
	}
	if (node->left)
		msh_handle_tree_heredocs(data, node->left);
	if (node->right)
		msh_handle_tree_heredocs(data, node->right);
}
