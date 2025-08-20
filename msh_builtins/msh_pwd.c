/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:33 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/19 16:55:49 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

int	msh_pwd(char *last_cwd, t_gc **gc)
{
	char	*pwd;

	if (!gc || !*gc)
		return (dbg_nullarg(__func__));
	pwd = gc_getcwd(gc);
	if (!pwd)
		pwd = last_cwd;
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
