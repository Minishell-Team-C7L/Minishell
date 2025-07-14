/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:26:44 by lhchiban          #+#    #+#             */
/*   Updated: 2024/11/16 13:04:17 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static unsigned	int	ft_n_len(int nb)
{
	unsigned int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		len += 1;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	unsigned int	len;
	char			*t;

	len = ft_n_len(n);
	t = (char *)malloc(sizeof(char) * (len + 1));
	if (t == NULL)
		return (t);
	if (n < 0)
	{
		t[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	if (nb == 0)
		t[0] = '0';
	t[len] = '\0';
	while (nb != 0)
	{
		t[len - 1] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	return (t);
}

