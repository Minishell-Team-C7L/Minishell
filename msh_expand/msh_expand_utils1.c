/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 05:10:29 by lhchiban          #+#    #+#             */
/*   Updated: 2025/08/24 05:19:38 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

static char **replace_with_split(char **arr, size_t i, char **split)
{
	size_t	len_arr;
	size_t	len_split;
	size_t	j;
	size_t	pos;
	char	**new_arr;

	len_arr = arr_len(arr);
	len_split = arr_len(split);
	new_arr = malloc((len_arr + len_split) * sizeof(char *));
	if (!new_arr)
		return (NULL);
	j = 0;
	pos = 0;
	while (j < i)
		new_arr[pos++] = arr[j++];
	j = 0;
	while (j < len_split)
		new_arr[pos++] = split[j++];
	j = i + 1;
	while (j < len_arr)
		new_arr[pos++] = arr[j++];
	new_arr[pos] = NULL;
	return (free(arr[i]), free(arr), free(split), new_arr);
}

char	**expand_and_split(char **f_expand, t_data *data)
{
	size_t	i;
	char	**extra_exp;

	i = 0;
	while (f_expand && f_expand[i])
	{
		f_expand[i] = msh_handel_expand(f_expand[i], data);
		if (data->dollar_exp_state)
		{
			extra_exp = msh_expand_split_args(f_expand[i]);
			if (extra_exp && extra_exp[1])
			{
				f_expand = replace_with_split(f_expand, i, extra_exp);
				i--;
			}
			else if (extra_exp)
				msh_free_arr(extra_exp);
		}
		i++;
	}
	return (f_expand);
}

void	msh_go_remove_quotes(char **f_expand)
{
	size_t	i;

	i = 0;
	while (f_expand && f_expand[i])
	{
		f_expand[i] = msh_rm_quates(f_expand[i]);
		i++;
	}
}

char	**msh_clean_empty_strs(char **arr)
{
	size_t	len;
	char	**new_arr;
	size_t	i;
	size_t	j;

	len = arr_len(arr);
	new_arr = malloc((len + 1) * sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	j = 0;
	while (arr[i])
	{
		if (arr[i][0] != '\0')
			new_arr[j++] = arr[i];
		else
			free(arr[i]);
		i++;
	}
	new_arr[j] = NULL;
	free(arr);
	return (new_arr);
}
