/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tree_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:44:16 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/23 16:21:34 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

static char	**static_set_up_exp_args(char *str, t_data *data);

void	msh_tree_init(t_data *data, t_node *tree_node)
{
	if (!tree_node)
		return ;
	if (tree_node->type == PIPE_N)
	{
		msh_tree_init(data, tree_node->left);
		msh_tree_init(data, tree_node->right);
	}
	else
	{
		if (tree_node->args)
			tree_node->arg = static_set_up_exp_args(tree_node->args, data);
	}
}

static char	**static_set_up_exp_args(char *str, t_data *data)
{
	size_t	i;
	char	**f_expand;

	f_expand = NULL;
	str = msh_handel_expand(str, data);
	if (!str)
		return (NULL);
	if (data->dollar_exp_state)
		str = msh_add_dqts_to_expval(str);
	if (!str)
		return (NULL);
	f_expand = msh_expand_split_args(str);
	free(str);
	if (!f_expand)
		return (NULL);
	i = -1;
	f_expand[0] = msh_rm_quates(f_expand[0]);
	while (f_expand[++i])
	{
		if ((data->dollar_exp_state && !ft_strcmp(f_expand[0], "export"))
			|| !data->dollar_exp_state)
			f_expand[i] = msh_rm_quates(f_expand[i]);
	}
	return (f_expand);
}
