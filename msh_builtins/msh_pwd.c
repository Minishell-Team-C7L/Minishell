/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:33 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/30 10:13:31 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

int	msh_pwd(t_gc **gc)
{
	char	*pwd;

	if (!gc || !*gc)
		return (dbg_nullarg(__func__));
	pwd = gc_getcwd(gc);
	if (!pwd)
		return (msh_perror("pwd"));
	ft_putstr_nl(pwd);
	return (EXIT_SUCCESS);
}
