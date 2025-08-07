/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:44:00 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/06 10:10:07 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

static t_gc	**static_expand_print_heredoc(
				t_data *data, char *read_line, size_t *j, int fd);

void	msh_expand_heredoc(int fd, char *read_line, t_data *data)
{
	size_t	j;
	t_gc	**gc;

	j = 0;
	while (read_line[j])
	{
		if (read_line[j] != '$')
		{
			ft_putchar_fd(read_line[j], fd);
			j++;
		}
		else
			gc = static_expand_print_heredoc(data, read_line, &j, fd);
	}
	gc_free(gc);
	ft_putnbr_fd('\n', fd);
}

static t_gc	**static_expand_print_heredoc(
	t_data *data, char *read_line, size_t *j, int fd)
{
	char	*temp;
	size_t	start;
	t_gc	**gcl;

	gcl = NULL;
	start = ++(*j);
	if (read_line[*j] == '?')
	{
		ft_putchar_fd(data->exit_status, fd);
		(*j)++;
		return (NULL);
	}
	while (read_line[*j] && read_line[*j] != ' ' && read_line[*j] != '$')
		(*j)++;
	if (*j != start)
	{
		temp = gc_substr(read_line, start, *j - start, gcl);
		// temp = env_get_value(data->env, temp);
		if (temp)
			ft_putstr_fd(temp, fd);
	}
	return (gcl);
}
