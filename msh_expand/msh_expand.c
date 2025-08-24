/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:17:27 by spi               #+#    #+#             */
/*   Updated: 2025/08/24 19:49:34 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"

static char	*msh_dollar_expand(size_t *i, char *args, t_data *data);
static char	*msh_double_quote_expand(size_t *i, char *args, t_data *data);
static char	*msh_single_quote_expand(size_t *i, char *args);
static char	*msh_no_expand(size_t *i, char *args);

char	*msh_handel_expand(char *args, t_data *data)
{
	char	*after_expand;
	size_t	i;

	i = 0;
	after_expand = ft_strdup("");
	data->dollar_exp_state = false;
	while (args[i])
	{
		if (args[i] == '$')
			after_expand = msh_strjoin_and_free(after_expand,
					msh_dollar_expand(&i, args, data));
		else if (args[i] == '"')
			after_expand = msh_strjoin_and_free(after_expand,
					msh_double_quote_expand(&i, args, data));
		else if (args[i] == '\'')
			after_expand = msh_strjoin_and_free(after_expand,
					msh_single_quote_expand(&i, args));
		else
			after_expand = msh_strjoin_and_free(after_expand,
					msh_no_expand(&i, args));
	}
	if (!after_expand)
		return (NULL);
	return (after_expand);
}

static char	*msh_dollar_expand(size_t *i, char *args, t_data *data)
{
	char	*variable;
	char	*env_value;
	size_t	start;
	size_t	j;

	(*i)++;
	if (args[*i] == '?')
		return ((*i)++, ft_itoa(data->exit_status));
	else if (!msh_variable_is_valid(args[*i]))
		return (ft_strdup("$"));
	else
		start = *i;
	data->dollar_exp_state = true;
	while (msh_variable_is_valid(args[*i]))
		(*i)++;
	variable = ft_substr(args, start, *i - start);
	env_value = msh_env_get_val(data->env, variable);
	if (!env_value)
		return (free(variable), ft_strdup(""));
	hide_quotes(env_value);
	j = 0;
	return (free(variable), ft_strdup(env_value));
}

static char	*msh_double_quote_expand(size_t *i, char *args, t_data *data)
{
	char	*res;

	res = ft_strdup("\"");
	(*i)++;
	while (args[*i] != '"')
	{
		if (args[*i] != '$')
			res = msh_strjoin_and_free(res, msh_dquote_extra(i, args));
		else
			res = msh_strjoin_and_free(res, msh_dollar_expand(i, args, data));
	}
	(*i)++;
	return (msh_strjoin_and_free(res, ft_strdup("\"")));
}

static char	*msh_single_quote_expand(size_t *i, char *args)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (args[*i] != '\'')
	{
		(*i)++;
	}
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
