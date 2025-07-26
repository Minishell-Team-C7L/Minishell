/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 08:18:13 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/19 16:22:25 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

void	msh_quit(int status, t_env **env, t_gc **gc)
{
	env_list_free(env);
	gc_free(gc);
	exit(status);
}
