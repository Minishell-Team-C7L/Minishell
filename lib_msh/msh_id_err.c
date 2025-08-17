/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_id_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:30:03 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/18 10:03:44 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

void	msh_id_err(const char *arg, const char *cmd)
{
	ft_puterr("msh: ");
	ft_puterr(cmd);
	ft_puterr(": `");
	ft_puterr(arg);
	ft_puterr(": not a valid identifier\n");
}
