/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_puterr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:02:05 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/08 18:57:15 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

void	msh_puterr(const char *cmd_name, const char *msg)
{
	if (cmd_name)
	{
		ft_puterr(PROJ_NAME);
		ft_puterr(cmd_name);
		ft_puterr(": ");
	}
	if (msg)
		ft_puterr(msg);
	ft_puterr("\n");
}
