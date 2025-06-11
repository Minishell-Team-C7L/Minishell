/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:08:15 by aessaber          #+#    #+#             */
/*   Updated: 2025/05/21 19:53:36 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

void	ft_putstr(char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = 0;
	while (str[len])
		len++;
	write(STDOUT_FILENO, str, len);
}
