/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:49:20 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/01 17:11:48 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

int	msh_currtoken_pip(t_token *curr_token)
{
	t_token_types	curr_type;

	if (!curr_token)
		return (0);
	curr_type = (*curr_token).type;
	if (curr_type == PIPE_T)
		return (1);
	return (0);
}

void	msh_next_token(t_data *cur_data)
{
	cur_data->cur_tokens = cur_data->cur_tokens->next;
}

t_node	*msh_tree(t_data *data)
{
	t_node	*left;
	t_node	*right;

	if (!data->cur_tokens)
		return (NULL);
	left = before_pip(data);
	if (!left)
		return (NULL);
	while (msh_currtoken_pip(data->cur_tokens))
	{
		msh_next_token(data);
		if (!data->cur_tokens)
			return (data->err_prs.perr_type = SYN_E, left); // set err
		right = msh_tree(data);
		if (!right)
			return (left);
		left = msh_head_combine(data, left, right);
		if (!left)
		{
			// msh_clear_tree(&left);
			// msh_clear_tree(&right);
			return (NULL);
		}
	}
	return (left);
}

t_node	*to_parse(t_data *data)
{
	t_node	*cur_abs;

	data->cur_tokens = data->token;
	cur_abs = msh_tree(data);
	if (data->cur_tokens)
		return (cur_abs);
	return (cur_abs);
}

t_node	*before_pip(t_data *cur_data)
{
	t_node		*cmd_b_pip;
	t_red_node	*red_list;
	t_red_node	*last_red;

	if (!msh_red_list(cur_data, &red_list))
		return (NULL);
	cmd_b_pip = msh_build_cmd_with_args(cur_data);
	if (!cmd_b_pip)
		return (msh_red_list_clear(&red_list), NULL);
	cmd_b_pip->red_l = red_list;
	if (!msh_red_list(cur_data, &red_list))
		return (msh_clear_cmd(cmd_b_pip), NULL);
	if (red_list)
	{
		if (cmd_b_pip->red_l)
		{
			last_red = cmd_b_pip->red_l;
			while (last_red->next)
				last_red = last_red->next;
			last_red->next = red_list;
		}
		else
			cmd_b_pip->red_l = red_list;
	}
	return (cmd_b_pip);
}
