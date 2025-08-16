/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_perror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:58:31 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/16 15:47:15 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

int	msh_perror(const char *cmd_name)
{
	ft_puterr(PROJECT_NAME);
	ft_puterr(": ");
	perror(cmd_name);
	return (EXIT_FAILURE);
}
