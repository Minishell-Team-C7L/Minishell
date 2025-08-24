/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:44:00 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/24 12:59:41 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

static int	msh_expand_w_hd(t_data *data,
				char *read_line, size_t j, int fd);

void	msh_expand_heredoc(int fd, char *str, t_data *data, bool sign)
{
	size_t	j;
	size_t	start;

	start = 0;
	j = 0;
	data->heredoc_expand_inqts = false;
	if (sign == true)
	{
		while (str[j])
		{
			if (str[j] != '$')
				(ft_putchar_fd(str[j], fd), j++);
			else
			{
				start = ++j;
				while (str[j] && str[j] != '\'' && str[j] != ' '
					&& str[j] != '"' && str[j] != '$')
					j++;
				msh_expand_w_hd(data, ft_substr(str, start, j - start), 0, fd);
			}
		}
	}
	else
		while (str[j])
			ft_putchar_fd(str[j++], fd);
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

static int	msh_expand_w_hd(
	t_data *data, char *read_line, size_t j, int fd)
{
	char	*value;

	value = NULL;
	if (read_line[j] == '?')
	{
		ft_putnbr_fd(data->exit_status, fd);
		return (2);
	}
	value = msh_env_get_val(data->env, read_line);
	if (value)
		ft_putstr_fd(value, fd);
	free(read_line);
	return (0);
}

size_t	arr_len(char **arr)
{
	size_t	len;

	len = 0;
	if (!arr)
		return (0);
	while (arr[len])
		len++;
	return (len);
}
