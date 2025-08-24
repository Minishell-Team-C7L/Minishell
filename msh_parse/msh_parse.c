/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:49:20 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/22 01:20:06 by lhchiban         ###   ########.fr       */
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

t_node	*msh_tree(t_data *data)
{
	t_node	*left;
	t_node	*right;

	if (!data->cur_tokens || data->err_prs.perr_type)
		return (NULL);
	left = before_pip(data);
	if (!left)
		return (NULL);
	while (msh_currtoken_pip(data->cur_tokens))
	{
		data->cur_tokens = data->cur_tokens->next;
		if (!data->cur_tokens)
			return (data->err_prs.perr_type = SYN_E, left);
		right = msh_tree(data);
		if (!right)
			return (left);
		left = msh_head_combine(data, left, right);
		if (!left)
		{
			msh_clear_tree(data, &left);
			msh_clear_tree(data, &right);
			return (NULL);
		}
	}
	return (left);
}

t_node	*to_parse(t_data *data)
{
	t_node	*cur_ast;

	data->cur_tokens = data->token;
	cur_ast = msh_tree(data);
	if (data->cur_tokens)
		return (data->err_prs.perr_type = SYN_E, cur_ast);
	return (cur_ast);
}

t_node	*before_pip(t_data *cur_data)
{
	t_node		*cmd_node;

	if (msh_currtoken_pip(cur_data->cur_tokens))
		cur_data->err_prs.perr_type = SYN_E;
	if (cur_data->err_prs.perr_type)
		return (NULL);
	cmd_node = msh_new_node(CMD_N);
	if (!cmd_node)
		return (cur_data->err_prs.perr_type = MEMO_E, NULL);
	while (cur_data->cur_tokens
		&& cur_data->cur_tokens->type != PIPE_T)
	{
		if (cur_data->cur_tokens->type == WORD_T)
		{
			if (!msh_build_cmd_with_args(cur_data, &(cmd_node->args)))
				return (cur_data->err_prs.perr_type = MEMO_E,
					msh_clear_cmd(cmd_node, cur_data), NULL);
		}
		else if (msh_is_red(cur_data, cur_data->cur_tokens->type))
		{
			if (!msh_red_list(cur_data, &(cmd_node->red_l)))
				return (free(cmd_node->args), free(cmd_node), NULL);
		}
	}
	return (cmd_node);
}

bool	msh_check_heredoc(char *delimiter)
{
	char	*sign;

	sign = delimiter;
	if (!sign)
		return (false);
	while (*sign && *sign != '\'' && *sign != '"')
		sign++;
	if (!*sign)
		return (true);
	return (false);
}
