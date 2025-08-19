/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_null_guard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:18:56 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/18 17:48:00 by lhchiban         ###   ########.fr       */
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
