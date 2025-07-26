/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:33 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/20 11:52:55 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

int	msh_pwd(t_gc **gc)
{
	char	*pwd;

	if (!gc || !*gc)
		return (dbg_nullarg(__func__), EXIT_FAILURE);
	pwd = gc_getcwd(gc);
	if (!pwd)
		return (msh_perror("pwd"), EXIT_FAILURE);
	ft_putstr_nl(pwd);
	return (EXIT_SUCCESS);
}
