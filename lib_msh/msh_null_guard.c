/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_null_guard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:18:56 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/19 16:22:25 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

void	*msh_null_guard(void *ptr, t_env **env, t_gc **gc)
{
	if (!ptr)
	{
		env_list_free(env);
		gc_free(gc);
		perror("msh");
		exit(2);
	}
	return (ptr);
}
