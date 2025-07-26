/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:40:33 by lhchiban          #+#    #+#             */
/*   Updated: 2025/07/26 11:05:31 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

t_node	*msh_head_combine(t_data *cur_data, t_node *left, t_node *right)
{
	t_node	*head_node;

	head_node = msh_new_node(PIPE_N);
	if (!head_node)
		return (cur_data->err_prs.perr_type = MEMO_E, NULL);
	head_node->left = left;
	head_node->right = right;
	return (head_node);
}

int	msh_add_arg_to_string(char **args, char *value)
{
	char	*temp;

	if (!value)
		return (0);
	if (!*args)
	{
		*args = ft_strdup(value);
		if (!*args)
			return (0);
	}
	else
	{
		temp = ft_strjoin(*args, " ");
		if (!temp)
			return (0);
		free(*args);
		*args = ft_strjoin(temp, value);
		free(temp);
		if (!*args)
			return (0);
	}
	return (1);
}

int     msh_build_args_string(char **args, t_data *cur_data)
{
        *args = NULL;
        while (cur_data->cur_tokens && cur_data->cur_tokens->type)
        {
			if (msh_is_red(cur_data->cur_tokens->type))
			{
				msh_next_token(cur_data);
				if (cur_data->cur_tokens && cur_data->cur_tokens->type == WORD_T)
					msh_next_token(cur_data);
			}
			if (cur_data->cur_tokens)
			{
				if (!msh_add_arg_to_string(args, cur_data->cur_tokens->val))
				{
						msh_free_args_string(args);
						return (cur_data->err_prs.perr_type = MEMO_E, 0);
				}
				msh_next_token(cur_data);
			}
        }
        return (1);
}

t_node	*msh_build_cmd_with_args(t_data *cur_data)
{
	t_node	*cmd_node;

	cmd_node = msh_new_cmd_node();
	if (!cmd_node)
		return (cur_data->err_prs.perr_type = MEMO_E, NULL);
	if (!msh_build_args_string(&cmd_node->args, cur_data))
	{
		free(cmd_node);
		return (NULL);
	}
	return (cmd_node);
}

bool	msh_red_list(t_data *cur_data, t_red_node **red_list)
{
	t_red_node	*red_node;

	*red_list = NULL;
	while (cur_data->cur_tokens && msh_is_red(cur_data->cur_tokens->type))
	{
		red_node = msh_new_red_node(cur_data->cur_tokens->type);
		if (!red_node)
			return (cur_data->err_prs.perr_type = MEMO_E, false);
		msh_next_token(cur_data);
		if (!cur_data->cur_tokens || cur_data->cur_tokens->type != WORD_T)
			return (cur_data->err_prs.perr_type = SYN_E, false);
		red_node->val = ft_strdup(cur_data->cur_tokens->val);
		if (!red_node->val)
			return (cur_data->err_prs.perr_type = MEMO_E, false);
		msh_combine_rediractions(red_node, red_list);
		msh_next_token(cur_data);
	}
	return (true);
}
