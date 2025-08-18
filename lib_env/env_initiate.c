/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initiate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:09:54 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/18 17:47:07 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"
#include "msh_main.h"

static bool	static_str_to_env_node(t_env **env, const char *str_envp);
static char	*static_get_variable(const char *str_envp);
static char	*static_get_value(const char *str_envp);

t_env	*env_initiate(char **ary_envp)
{
	t_env	*env;
	size_t	row;

	if (!ary_envp)
		return (NULL);
	env = NULL;
	row = 0;
	while (ary_envp[row])
	{
		if (!static_str_to_env_node(&env, ary_envp[row]))
			return (env_list_free(&env), NULL);
		row++;
	}
	return (env);
}

static bool	static_str_to_env_node(t_env **env, const char *str_envp)
{
	t_env	*new_node;
	char	*variable;
	char	*value;

	variable = static_get_variable(str_envp);
	value = static_get_value(str_envp);
	if (!variable || !value)
		return (ft_free((void **)&variable), ft_free((void **)&value), false);
	new_node = env_node_alloc();
	if (!new_node)
		return (ft_free((void **)&variable), ft_free((void **)&value), false);
	if (!env_node_fill(new_node, variable, value))
	{
		ft_free((void **)&variable);
		ft_free((void **)&value);
		env_node_free(&new_node);
		return (false);
	}
	env_node_add_back(env, new_node);
	return (ft_free((void **)&variable), ft_free((void **)&value), true);
}

static char	*static_get_variable(const char *str_envp)
{
	char	*variable;
	size_t	col;

	col = 0;
	while (str_envp[col] && str_envp[col] != '=')
		col++;
	variable = ft_substr(str_envp, 0, col);
	if (!variable)
		return (NULL);
	return (variable);
}

static char	*static_get_value(const char *str_envp)
{
	char	*value;
	size_t	col;

	col = 0;
	while (str_envp[col] && str_envp[col] != '=')
		col++;
	if (!str_envp[col])
		return (ft_strdup(""));
	value = ft_strdup(str_envp + col +1);
	if (!value)
		return (NULL);
	return (value);
}
