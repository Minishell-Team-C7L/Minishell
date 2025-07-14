/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:19:45 by lhchiban          #+#    #+#             */
/*   Updated: 2024/11/16 13:06:36 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int	tab[10];
	int	i;

	i = 0;
	if (nb != -2147483648 && nb < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', fd);
	}
	if (nb == -2147483648)
		write(fd, "-2147483648", 11);
	if (nb == 0)
		write(fd, "0", 1);
	while (nb > 0)
	{
		tab[i] = nb % 10;
		nb = nb / 10;
		i++;
	}
	while (i > 0)
		ft_putchar_fd(tab[--i] + 48, fd);
}
