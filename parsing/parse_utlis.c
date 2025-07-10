/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:40:33 by lhchiban          #+#    #+#             */
/*   Updated: 2025/07/05 01:43:08 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node *msh_head_combine(t_data *cur_data ,t_node *left, t_node *right)
{
	t_node *head_node;

	head_node = msh_new_node(PIPE_N); // imkn tbadeel type wa9ila
	if (!head_node)
		return (cur_data->err_prs.perr_type = MEMO_E ,NULL); // must set err in memory her
	head_node->left = left;
	head_node->right = right;
	return (head_node);
}

t_node *msh_new_node(t_node_type type)
{
	t_node *new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

int	msh_join_args(char **args, t_token *cur_token, t_data *cur_data)
{
	char *tmp;

	if (cur_data->err_prs.perr_type)
		return (0);
	if (!*args)
		*args = ft_strdup("");
	if (!*args)
		return (0);
	while (cur_token && cur_token->type == WORD_T)
	{
		tmp = *args;
		*args = msh_join_args_sp(cur_token->val, *args, ' ');
		if (!*args)
		{
			free(tmp);
			return (0);
		}
		cur_token = cur_token->next;
	}
	return (1);
}

char *msh_join_args_sp(const char *token_val, const char *arg, char sp)
{
	char *final_arg;
	size_t j;
	size_t i;

	if (!token_val && !arg)
		return (NULL);
	if (!arg || !token_val)
		return (ft_strjoin(token_val, arg));
	final_arg = ft_calloc(ft_strlen(token_val) + ft_strlen(arg) + 2,
		sizeof(char));
	if (!final_arg)
		return (NULL);
	i = -1;
	while (arg[++i])
		final_arg[i] = arg[i];
	final_arg[i] = sp;
	j = -1;
	while (token_val[++j])
		final_arg[i++] = token_val[j];
	final_arg[i] = '\0';
	return (final_arg);
}
