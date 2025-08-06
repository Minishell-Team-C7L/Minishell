/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:40:33 by lhchiban          #+#    #+#             */
/*   Updated: 2025/08/06 06:36:00 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

t_node	*msh_head_combine(t_data *cur_data, t_node *left, t_node *right)
{
	t_node	*head_node;

	if (cur_data->err_prs.perr_type)
        return (NULL);
	head_node = msh_new_node(PIPE_N);
	if (!head_node)
		return (cur_data->err_prs.perr_type = MEMO_E, NULL);
	head_node->left = left;
	head_node->right = right;
	return (head_node);
}

static  char	*msh_strjoin_sp(char const *s1, char const *s2)
{
	size_t	total_l;
	char	* joinw;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	if (!ft_strlen(s1) || !ft_strlen(s2))
		return (ft_strjoin(s1, s2));
	total_l = ft_strlen(s1) + ft_strlen(s2) + 1 + 1;
	joinw = ft_calloc(total_l, sizeof(char));
	if (!joinw)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joinw[i] = s1[i];
		i++;
	}
	joinw[i++] = ' ';
	j = 0;
	while (s2[j])
		joinw[i++] = s2[j++];
	joinw[i] = '\0';
	return (joinw);
}


int	msh_build_cmd_with_args(t_data *cur_data, char **args)
{
	char	*free_args;

	if (!*args)
		*args = ft_strdup("");
	if (cur_data->err_prs.perr_type || !*args)
		return (free(*args), 0);
	while (cur_data->cur_tokens && cur_data->cur_tokens->type == WORD_T)
    {
		free_args = *args;
		*args = msh_strjoin_sp(cur_data->cur_tokens->val, *args);
		if (!*args)
			return (free(free_args), 0);
		free(free_args);
		msh_next_token(cur_data);
    }
	return (1);;
}

bool	msh_red_list(t_data *cur_data, t_red_node **red_list)
{
	t_red_node	*red_node;
	t_token_types	red_type;

	*red_list = NULL;
	if (cur_data->err_prs.perr_type)
		return (false);
	while (cur_data->cur_tokens && msh_is_red(cur_data->cur_tokens->type))
	{
		red_type = cur_data->cur_tokens->type;
		msh_next_token(cur_data);
		if (!cur_data->cur_tokens || cur_data->cur_tokens->type != WORD_T)
			return (cur_data->err_prs.perr_type = SYN_E, false);
		red_node = msh_new_red_node(cur_data->cur_tokens->val, red_type);
		if (!red_node)
			return (cur_data->err_prs.perr_type = MEMO_E, false);
		msh_combine_rediractions(red_node, red_list);
		msh_next_token(cur_data);
	}
	return (true);
}

void	msh_clear_tree(t_data *cur_data, t_node **tree)
{
	msh_clear_tree_rec(*tree);
	*tree = NULL;
	free_token_list(&cur_data->token);
}
