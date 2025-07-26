/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:51:26 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 05:00:10 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_ENV_H
# define LIB_ENV_H

# include "lib_ft.h"
# include "lib_dbg.h"

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*env_get_node(t_env **env, const char *target_variable);
t_env	*env_get_node_prev(t_env **env, const char *target_variable);
t_env	*env_initiate(char **ary_envp);
void	env_list_free(t_env **env);
void	env_node_add_back(t_env **env, t_env *new_node);
t_env	*env_node_alloc(void);
void	env_node_del(t_env **env, const char *variable);
t_env	*env_node_fill(
			t_env *env_node, const char *variable, const char *value);
void	env_node_free(t_env **env_node);
t_env	*env_node_set(
			t_env **env, const char *target_var, const char *new_value);
t_env	*env_node_update(t_env *env_node, const char *new_value);
t_env	*env_sort(t_env *env_list);

#endif