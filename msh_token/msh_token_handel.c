/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_token_handel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:49:05 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/17 03:55:18 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_token.h"

t_token	*to_tokens(t_data *data)
{
	t_token	*final_token_l;
	char	*f_line;

	f_line = data->line;
	final_token_l = ft_fill_tokens(f_line, data);
	free(f_line);
	data->line = NULL;
	return (final_token_l);
}

t_token	*ft_fill_tokens(char *line, t_data *data)
{
	t_token	*list_of_t;
	int		err;

	list_of_t = NULL;
	err = 0;
	while (*line)
	{
		if (0 != err)
			return (free_token_list(&list_of_t), NULL);
		skip_whitespace(&line);
		if (is_special_char(*line))
			err = (1 && !msh_check_stoken_type(&list_of_t, &line, data));
		else
			err = (1 && !msh_check_ntoken_type(&list_of_t, &line, data));
	}
	return (list_of_t);
}

int	msh_check_ntoken_type(t_token **list_of_t, char **token_value, t_data *data)
{
	t_token	*token;
	char	*tmp;
	char	*val;
	size_t	j;

	j = 0;
	tmp = *token_value;
	while (tmp[j] && tmp[j] != '\n'
		&& tmp[j] != ' ' && !msh_is_operator((tmp + j)))
	{
		if (!msh_is_quote(tmp[j]))
			j++;
		else
			if (!msh_skip_quates(&j, tmp))
				return (msh_quates_err(data), 0);
	}
	val = ft_substr(tmp, 0, j);
	if (!val)
		return (0);
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (free(val), 0);
	token->type = WORD_T;
	token->val = val;
	return (*token_value += j, token_list_add(list_of_t, token), 1);
}

int	msh_check_stoken_type(t_token **list_of_t, char **token_value, t_data *data)
{
	if (!ft_strncmp(*token_value, "|", 1))
		return (1 && add_token_type(list_of_t, token_value, PIPE_T));
	else if (!ft_strncmp(*token_value, "<<", 2))
	{
		data->heredoc_count++;
		return (1 && add_token_type(list_of_t, token_value, HERE_DOC_T));
	}
	else if (!ft_strncmp(*token_value, ">>", 2))
		return (1 && add_token_type(list_of_t, token_value, REDIR_APPEND_T));
	else if (!ft_strncmp(*token_value, "<", 1))
		return (1 && add_token_type(list_of_t, token_value, REDIR_IN_T));
	else
		return (1 && add_token_type(list_of_t, token_value, REDIR_OUT_T));
}

int	add_token_type(t_token **t_list, char **cur_token, t_token_types t_type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->type = t_type;
	new_token->val = NULL;
	token_list_add(t_list, new_token);
	if (t_type == HERE_DOC_T || t_type == REDIR_APPEND_T)
		(*cur_token)++;
	(*cur_token)++;
	return (1);
}
