/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:40:33 by lhchiban          #+#    #+#             */
/*   Updated: 2025/07/13 18:43:20 by lhchiban         ###   ########.fr       */
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

t_node *msh_new_node(t_node_type n_type)
{
	t_node 		*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = n_type;
	return (new_node);
}

t_red_node *msh_new_red_node(t_token_types t_type)
{
	t_red_node *red_n_node;

	red_n_node = (t_red_node *)ft_calloc(1, sizeof(t_red_node));
	if (!red_n_node)
		return NULL;
	red_n_node->val = ft_strdup(NULL);
	red_n_node->type = msh_red_type(t_type);
	if (!red_n_node->type)
		return(free(red_n_node), NULL);
	return (red_n_node);
}

int	msh_join_args(char **args, t_data *cur_data)
{
	char *tmp;

	*args = NULL;
	while (cur_data->cur_tokens && cur_data->cur_tokens->type == WORD_T)
	{
		if (!*args)
		{
			*args = ft_strdup(cur_data->cur_tokens->val);
			if (!args)
				return (cur_data->err_prs.perr_type = MEMO_E, 0);
		}
		else
		{
			tmp = msh_join_args_sp(cur_data->cur_tokens->val, *args, " ");
			if (!tmp)
				return (cur_data->err_prs.perr_type = MEMO_E, 0);
			free(*args);
			*args = tmp;
		}
		msh_next_token(cur_data);
	}
	return (1);
}

char *msh_join_args_sp(const char *token_val, const char *arg, char *sp)
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
	final_arg[i] = *sp;
	j = -1;
	while (token_val[++j])
		final_arg[i++] = token_val[j];
	final_arg[i] = '\0';
	return (final_arg);
}

bool msh_red_list(t_data *cur_data, t_red_node **red_list)
{
	t_red_node *red_node;

	*red_list = NULL;// dont forget the defend for this
	while (cur_data->cur_tokens && msh_is_red(cur_data->cur_tokens->type))
	{
		red_node = msh_new_red_node(cur_data->cur_tokens->type); //check if i node use this 3 option in her remove it
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

