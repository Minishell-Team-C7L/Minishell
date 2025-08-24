/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tree_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:44:16 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/24 19:44:58 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

static char	**static_set_up_exp_args(char *str, t_data *data);
static int	msh_keyval_valid(const char *variable);

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

static void	msh_handle_export_args(char **f_expand)
{
	size_t	i;

	if (!ft_strncmp(f_expand[0], "export", 7))
	{
		i = 1;
		while (f_expand[i])
		{
			if (msh_keyval_valid(f_expand[i]))
				f_expand[i] = msh_add_dqts_to_expval(f_expand[i]);
			else
				i++;
		}
	}
}

static char	**static_set_up_exp_args(char *str, t_data *data)
{
	char	**f_expand;

	f_expand = msh_expand_split_args(str);
	if (!f_expand)
		return (NULL);
	f_expand = expand_and_split(f_expand, data);
	msh_handle_export_args(f_expand);
	if (!f_expand)
		return (NULL);
	msh_go_remove_quotes(f_expand);
	if (!f_expand)
		return (NULL);
	if (ft_strcmp(f_expand[0], "export") && is_only_quotes(f_expand[0]))
		f_expand = msh_clean_empty_strs(f_expand);
	return (f_expand);
}

static int	msh_keyval_valid(const char *variable)
{
	int	col;

	col = 0;
	while (variable[col])
	{
		if (!ft_isalnum(variable[col]) && variable[col] != '_')
			return (0);
		col++;
	}
	col = 0;
	while (variable[col] && (ft_isalnum(variable[col]) || variable[col] == '_'))
		col++;
	if (variable[col] == '+' && variable[col +1] == '=' && variable[col +2])
		return (1);
	if (variable[col] == '+' && variable[col +1])
		return (1);
	return (0);
}
