/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:07:31 by aessaber          #+#    #+#             */
/*   Updated: 2025/05/21 19:53:33 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

void	ft_puterr(char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = 0;
	while (str[len])
		len++;
	write(STDERR_FILENO, str, len);
}
