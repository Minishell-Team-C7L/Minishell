/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:17:27 by spi               #+#    #+#             */
/*   Updated: 2025/07/25 19:47:35 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

static char	*msh_dollar_expand(size_t *i, char *args, t_data *data);
static char	*msh_double_quote_expand(size_t *i, char *args, t_data *data);
static char	*msh_single_quote_expand(size_t *i, char *args);
static char	*msh_no_expand(size_t *i, char *args);

char	**msh_handel_expand(char *args, t_data *data)
{
	char	*after_expand;
	char	**res;
	size_t	i;

	i = 0;
	after_expand = ft_strdup("");
	while (args[i])
	{
		if (args[i] == '$')
			after_expand = ft_strjoin(
					after_expand, msh_dollar_expand(&i, args, data));
		else if (args[i] == '"')
			after_expand = ft_strjoin(
					after_expand, msh_double_quote_expand(&i, args, data));
		else if (args[i] == '\'')
			after_expand = ft_strjoin(
					after_expand, msh_single_quote_expand(&i, args));
		else
			after_expand = ft_strjoin(after_expand, msh_no_expand(&i, args));
	}
	if (!after_expand)
		return (NULL);
	res = msh_expand_split_args(after_expand);
	free(after_expand);
	if (!res)
		return (NULL);
	return (res);
}

static char	*msh_dollar_expand(size_t *i, char *args, t_data *data)
{
	char	*variable;
	char	*env_value;
	size_t	start;

	(*i)++;
	if (args[*i] == '@' || ft_isdigit(args[*i]))
		return ((*i)++, ft_strdup(""));
	else if (args[*i] == '?')
		return ((*i)++, ft_itoa(data->exit_status));
	else if (!msh_variable_is_valid(args[*i]))
		return (ft_strdup("$"));
	else
		start = *i;
	while (msh_variable_is_valid(args[*i]))
		(*i)++;
	variable = ft_substr(args, start, *i - start);
	// env_value = env_get_value(data->env, variable);
	env_value = NULL;
	if (!env_value)
	{
		free(variable);
		return (ft_strdup(""));
	}
	return (free(variable), ft_strdup(env_value));
}

static char	*msh_double_quote_expand(size_t *i, char *args, t_data *data)
{
	char	*res;

	res = ft_strdup("\"");
	(*i)++;
	while (args[*i] != '"')
	{
		if (args[*i] == '$')
			res = ft_strjoin(res, msh_dollar_expand(i, args, data));
		// else if (str[*i] == '\'')
		//     res = ft_strjoin(res, msh_single_quote_expand(i, args));
		else
			res = ft_strjoin(res, msh_dquote_extra(i, args));
	}
	(*i)++;
	return (ft_strjoin(res, ft_strdup("\"")));
}

// imkn ikono fiha errors
static char	*msh_single_quote_expand(size_t *i, char *args)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (args[*i] != '\'')
	{
		if (args[*i] == '\0')
			break ;
		(*i)++;
	}
	if (args[*i] == '\'')
		(*i)++;
	return (ft_substr(args, start, *i - start));
}

static char	*msh_no_expand(size_t *i, char *args)
{
	size_t	str_s;

	str_s = *i;
	while (args[*i] && args[*i] != '$' && args[*i] != '"' && args[*i] != '\'')
		(*i)++;
	return (ft_substr(args, str_s, *i - str_s));
}
