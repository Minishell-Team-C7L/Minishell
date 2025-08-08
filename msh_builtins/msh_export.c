/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:30 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/07 16:00:37 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

static int	export_print(t_env **env, t_gc **gc);
static int	export_parse_arg(const char *arg, t_env **env, t_gc **gc);
static int	export_append(const char *arg, t_env **env, t_gc **gc);

int	msh_export(const char **arg, t_env **env, t_gc **gc)
{
	int		row;
	uint8_t	exit_status;

	if (!arg || !*arg || !env || !gc || !*gc)
		return (dbg_nullarg(__func__));
	row = 1;
	exit_status = EXIT_SUCCESS;
	if (!arg[row])
		return (export_print(env, gc));
	while (arg[row])
	{
		if (export_parse_arg(arg[row], env, gc) == EXIT_FAILURE)
			exit_status = EXIT_FAILURE;
		row++;
	}
	return (exit_status);
}

static int	export_print(t_env **env, t_gc **gc)
{
	t_env	*env_sorted;
	t_env	*env_node;

	env_sorted = (t_env *)msh_null_guard(msh_env_sort(env, gc), env, gc);
	env_node = env_sorted;
	while (env_node)
	{
		if (ft_strcmp(env_node->variable, "_") != 0)
		{
			ft_putstr("declare -x ");
			ft_putstr(env_node->variable);
			if (env_node->value)
			{
				ft_putstr("=\"");
				ft_putstr(env_node->value);
				ft_putchar('\"');
			}
			ft_putchar('\n');
		}
		env_node = env_node->next;
	}
	return (EXIT_SUCCESS);
}

static int	export_parse_arg(const char *arg, t_env **env, t_gc **gc)
{
	int		col;
	char	*variable;
	char	*value;

	col = 0;
	if (!ft_isalpha(arg[col]) && arg[col] != '_')
		return (msh_id_err(arg, "export"), EXIT_FAILURE);
	while (arg[col] && (ft_isalnum(arg[col]) || arg[col] == '_'))
		col++;
	if (arg[col] == '+' && arg[col +1] == '=')
		return (export_append(arg, env, gc));
	if (arg[col] && arg[col] != '=')
		return (msh_id_err(arg, "export"), EXIT_FAILURE);
	variable = msh_env_var_parse(arg, env, gc);
	if (arg[col] == '=')
		value = msh_env_val_parse(arg, env, gc);
	else
		value = NULL;
	msh_null_guard(env_node_set(env, variable, value), env, gc);
	return (EXIT_SUCCESS);
}

static int	export_append(const char *arg, t_env **env, t_gc **gc)
{
	t_env	*env_node;
	char	*variable_parsed;
	char	*value_parsed;
	char	*old_value;

	variable_parsed = msh_env_var_parse(arg, env, gc);
	value_parsed = msh_env_val_parse(arg, env, gc);
	env_node = env_get_node(env, variable_parsed);
	if (env_node && env_node->value)
	{
		old_value = env_node->value;
		env_node->value = (char *)msh_null_guard(
				ft_strjoin(env_node->value, value_parsed), env, gc);
		ft_free((void **)&old_value);
	}
	else
		msh_null_guard(
			env_node_set(env, variable_parsed, value_parsed), env, gc);
	return (EXIT_SUCCESS);
}
