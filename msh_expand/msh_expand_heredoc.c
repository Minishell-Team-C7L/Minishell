/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:44:00 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/17 04:53:29 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

static int	static_expand_print_heredoc(t_data *data,
				char *read_line, size_t j, int fd);

void	msh_expand_heredoc(int fd, char *read_line, t_data *data, bool sign)
{
	size_t	j;

	j = 0;
	while (read_line[j])
	{
		if (read_line[j] != '$' && sign)
		{
			ft_putchar_fd(read_line[j], fd);
			j++;
		}
		else
			j += static_expand_print_heredoc(data, read_line, j, fd);
	}
	ft_putchar_fd('\n', fd);
}

char	*msh_env_get_val(t_env *env, const char *key)
{
	t_env	*env_node;

	env_node = env;
	while (env)
	{
		if (!ft_strcmp(env->variable, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	static_expand_print_heredoc(
	t_data *data, char *read_line, size_t j, int fd)
{
	char	*temp_val;
	size_t	start;

	start = ++j;
	if (read_line[j] == '?')
	{
		ft_putchar_fd(data->exit_status, fd);
		return (2);
	}
	while (read_line[j] && read_line[j] != ' ' && read_line[j] != '$')
		(j)++;
	if (j != start)
	{
		temp_val = gc_substr(read_line, start, j - start, &data->gc);
		temp_val = msh_env_get_val(data->env, temp_val);
		if (temp_val)
			ft_putstr_fd(temp_val, fd);
	}
	return (j);
}
