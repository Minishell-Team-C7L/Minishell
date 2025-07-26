/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_nullarg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:17:56 by aessaber          #+#    #+#             */
/*   Updated: 2025/06/24 06:30:05 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_dbg.h"

void	dbg_nullarg(const char *function_name)
{
	ft_puterr("DBG: ");
	ft_puterr(function_name);
	ft_puterr(": missing argument(s).\n");
}
