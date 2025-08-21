/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_var_parse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:10:09 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/19 20:01:36 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

char	*msh_env_var_parse(const char *variable, t_env **env, t_gc **gc)
{
	char	*var_end;
	char	*env_variable;
	size_t	len;

	var_end = ft_strchr(variable, '+');
	if (!var_end)
		var_end = ft_strchr(variable, '=');
	if (var_end)
		len = (size_t)(var_end - variable);
	else
		len = ft_strlen(variable);
	env_variable = (char *)msh_null_guard(
			gc_substr(variable, 0, len, gc), env, gc);
	return (env_variable);
}
