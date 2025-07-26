/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linerr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:48:50 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/25 19:41:20 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_token.h"

int	check_after_op(char *line_err, int line_index)
{
	while (line_index > 0)
	{
		line_err++;
		line_index--;
	}
	while (*line_err)
	{
		if (*line_err == ' ' || *line_err == '\t')
			line_err++;
		else
		{
			line_index++;
			line_err++;
		}
	}
	return (line_index);
}

int	op_calcule(char *line_err, char *operator)
{
	int		nm_op;
	char	*line_op;

	line_op = line_err;
	nm_op = 0;
	if (!line_op[-1] && *operator == '|')
		return (0);
	while (*line_err != ' ' && *line_err)
	{
		if (*line_err == *operator)
			nm_op++;
		++line_err;
	}
	if (!line_op[-1] && !check_after_op(line_op, nm_op))
		return (0);
	if (*operator == '|' && (nm_op > 1))
		return (0);
	else if ((*operator == '<' && nm_op > 3)
		|| (*operator == '>' && nm_op > 2) || (!line_op[-1]
			&& *operator == '<' && nm_op >= 2))
		return (0);
	else
		return (1);
}

int	ft_line_err(t_token **lst_of_t_err)
{
	// t_token *nexts;
	// t_token *cur_node;
	(void)lst_of_t_err;
	ft_putstr_fd("minishell: syntax error\n", 2);
	// cur_node = *lst_of_t_err;
	// if (!cur_node)
	// 	return 2;
	// while (cur_node)
	// {
	// 	free(cur_node->val);
	// 	nexts = cur_node->next;
	// 	free (cur_node);
	// 	cur_node = nexts;
	// }
	// *lst_of_t_err = NULL;
	return (0);
}

static int	quotes_op_calcule(char *line_err, char *quotes_op)
{
	int	nm_q;

	nm_q = 1;
	line_err++;
	while (*line_err)
	{
		if (*line_err == *quotes_op)
			nm_q++;
		line_err++;
	}
	return (nm_q);
}

int	check_line_errors(char **line)
{
	if (**line == '\'' || **line == '\"')
		return (quotes_op_calcule(*line, *line) % 2 == 0);
	else
		return (op_calcule(*line, *line));
}

int	check_line_err(char **line_err)
{
	int	nm_q;

	if (**line_err == '"')
		nm_q = quotes_op_calcule(*line_err, "\"");
	if (**line_err == '\'')
		nm_q = quotes_op_calcule(*line_err, "\'");
	if (**line_err == '|')
		return (op_calcule(*line_err, "|"));
	else if (**line_err == '<')
		return (op_calcule(*line_err, "<"));
	else if (**line_err == '>')
		return (op_calcule(*line_err, ">"));
	else if (**line_err == '&' || nm_q % 2 != 0)
		return (0);
	else
		return (1);
}
