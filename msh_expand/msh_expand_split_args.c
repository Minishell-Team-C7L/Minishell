/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_split_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:44:05 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/22 21:53:35 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

static void	msh_skip_w(char const *str, size_t	*j);
static char	**msh_args_allocat(char const *arg_str, char **dargs);
static char	**msh_fill(char **args, char const *str);
static void	msh_fill_words(char **args, const char *str, size_t j, size_t *i);

char	**msh_expand_split_args(char const *arg)
{
	size_t		i;
	size_t		j;
	char		**args;
	char		**free_arg;

	args = NULL;
	free_arg = NULL;
	if (!arg)
		return (NULL);
	j = 0;
	i = j;
	while (arg[i])
	{
		if ((arg[i] != ' ' && arg[i] != '\t') && ++j)
			msh_skip_w(arg, &i);
		while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
			i++;
	}
	args = ft_calloc(j + 1, sizeof(char *));
	free_arg = args;
	args = msh_args_allocat(arg, args);
	if (!args || !j)
		return (msh_free_arr(free_arg), NULL);
	return (msh_fill(args, arg));
}

static void	msh_skip_w(char const *str, size_t	*j)
{
	char	quotes;

	while (str[*j] && (str[*j] != ' ' && str[*j] != '\t'))
	{
		if (str[*j] != '\'' && str[*j] != '"')
			(*j)++;
		else
		{
			quotes = str[(*j)++];
			while (str[*j] && str[*j] != quotes)
				(*j)++;
			if (str[*j] == quotes)
				(*j)++;
			else
				return ;
		}
	}
}

static char	**msh_args_allocat(char const *arg_str, char **dargs)
{
	size_t	j;
	size_t	i;
	size_t	start;

	j = 0;
	i = 0;
	while (arg_str[i])
	{
		if (arg_str[i] != ' ' && arg_str[i] != '\t')
		{
			start = i;
			msh_skip_w(arg_str, &i);
			dargs[j] = ft_calloc(i - start + 1, sizeof(char));
			if (!dargs[j])
				return (NULL);
			j++;
		}
		while (arg_str[i] && (arg_str[i] == ' ' || arg_str[i] == '\t'))
			i++;
	}
	return (dargs);
}

static char	**msh_fill(char **args, char const *str)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = i;
	while (str[i] && args[j])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			msh_fill_words(args, str, j, &i);
			j++;
		}
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
	}
	return (args);
}

static void	msh_fill_words(char **args, const char *str, size_t j, size_t *i)
{
	size_t	c;
	char	quotes;

	c = 0;
	while (str[(*i)] && str[(*i)] != ' ' && str[*i] != '\t')
	{
		if (str[(*i)] != '\'' && str[(*i)] != '"')
			args[j][c++] = str[(*i)++];
		else
		{
			quotes = str[(*i)++];
			args[j][c++] = quotes;
			while (str[*i] && str[*i] != quotes)
				args[j][c++] = str[(*i)++];
			if (str[*i] == quotes)
				args[j][c++] = str[(*i)++];
		}
	}
	args[j][c] = '\0';
}
