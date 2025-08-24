/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_linemod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:44:58 by lhchiban          #+#    #+#             */
/*   Updated: 2025/08/24 00:18:30 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_token.h"

void	msh_quates_err(t_data *data)
{
	msh_print_fd("msh: syntax error", 2);
	data->exit_status = 258;
}

int	msh_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	msh_skip_quates(size_t *i, char *line)
{
	char	qts;

	qts = line[*i];
	if (ft_strchr(line + *i + 1, qts))
	{
		(*i)++;
		while (line[*i] != qts)
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

int	is_special_char(char c)
{
	return (c == '>'
		|| c == '<'
		|| c == '|');
	return (0);
}

void	skip_whitespace(char **line)
{
	while (**line > 0 && **line <= 32)
		(*line)++;
}
