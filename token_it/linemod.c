/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linemod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:44:58 by lhchiban          #+#    #+#             */
/*   Updated: 2025/07/10 00:05:36 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char *ft_skip_whitespaces(char *line)
{
	char *new_line;
	int i;
	int j;

	i  = 0;
	j = 0;
	while (line[i])
	{
		if ((ft_check_quotes(&line[i])))  // nab9a nwayli 3la toul dyal dakchi li wast lquote
			j++;
		else if (line[i] > 32)
			j++;
		else if ((line[i] > 0 && line[i] <= 32) && line[i +1] > 32)
			j++;
		else if (line[i] > 32 && line[i +1] > 0 && line[i +1] <= 32)
			j++;
		i++;
	}
	new_line = (char *)malloc(j -1 +1 * sizeof(char));
	if (!new_line)
		return (NULL);
	return (new_line);
}

char *ft_rm_whitespaces(char *line)
{
	char *new_line;
	// int quotes_state;
	int len;
	int i;

	if (!line)
		return (NULL);
	new_line = ft_skip_whitespaces(line);
	i = 0;
	len = 0;
	while (line[i] > 0 && line[i] <= 32)//
		i++;
	i -= 1;
	while (line[++i])
	{
		if ((ft_check_quotes(&line[i])))  // nab9a nwayli 3la toul dyal dakchi li wast lquote
			new_line[len++] = line[i];
		else if (line[i] > 32)
			new_line[len++] = line[i];
		else if (((line[i] > 0 && line[i] <= 32) && line[i +1] > 32))
			new_line[len++] = line[i];
	}
	new_line[len] = '\0';
	free (line);
	return (new_line);
}

int ft_check_quotes(char *line)
{
	static int quotes_state;
	if (!line)
		return 0;
	if ((*line == '\'' || *line == '\"') && !quotes_state)
		return (quotes_state = 1);
	if (*line == '\'' || *line == '\"')
		return (quotes_state = 0);
	return (quotes_state);
}
