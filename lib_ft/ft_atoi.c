/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:20:17 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 06:40:21 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

static int	static_is_whitespace(int c);
static int	static_is_digit(int c);
static int	static_is_overflowed(unsigned long num, char c, int sign);
static int	static_overflow_sign(int sign);

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	num;

	i = 0;
	while (static_is_whitespace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	num = 0;
	while (static_is_digit(str[i]))
	{
		if (static_is_overflowed(num, str[i], sign))
			return (static_overflow_sign(sign));
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(num * sign));
}

static int	static_is_whitespace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static int	static_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	static_is_overflowed(unsigned long num, char c, int sign)
{
	if (sign == -1)
		return (num > LONG_MAX / 10
			|| (num == LONG_MAX / 10 && (c - '0') > 8));
	else
		return (num > LONG_MAX / 10
			|| (num == LONG_MAX / 10 && (c - '0') > 7));
}

static int	static_overflow_sign(int sign)
{
	if (sign == -1)
		return (0);
	else
		return (-1);
}
