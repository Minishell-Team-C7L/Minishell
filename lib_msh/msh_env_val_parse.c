/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_val_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:10:09 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/19 20:01:20 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

char	*msh_env_val_parse(const char *value, t_env **env, t_gc **gc)
{
	const char	*val_start;

	if (!value || !gc || !*gc)
		return (dbg_nullarg(__func__), NULL);
	val_start = ft_strchr(value, '=');
	if (!val_start)
		return ((char *)msh_null_guard(gc_strdup("", gc), env, gc));
	return ((char *)msh_null_guard(gc_strdup(val_start +1, gc), env, gc));
}
