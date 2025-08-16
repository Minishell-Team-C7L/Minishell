/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_nullarg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:17:56 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/30 10:10:11 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_dbg.h"

int	dbg_nullarg(const char *function_name)
{
	ft_puterr("DBG: ");
	ft_puterr(function_name);
	ft_puterr(": missing argument(s).\n");
	return (EXIT_FAILURE);
}
