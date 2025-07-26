/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:45:33 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/18 11:04:05 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"

static int	static_is_whitespace(int c);
static bool	static_num_check(const char **digit);
static int	static_is_digit(int c);
static int	static_is_overflowed(unsigned long long_num, char c, int sign);

bool	ft_str_is_num(const char *str)
{
	const char	*digit;

	if (!str || !str[0])
		return (false);
	digit = str;
	while (static_is_whitespace(*digit))
		digit++;
	if (!static_num_check(&digit))
		return (false);
	while (static_is_whitespace(*digit))
		digit++;
	if (*digit)
		return (false);
	return (true);
}

static int	static_is_whitespace(int c)
{
	return (c == ' '
		|| (c >= '\t' && c <= '\r'));
}

static bool	static_num_check(const char **digit)
{
	unsigned long	long_num;
	int				sign;
	bool			has_num;

	long_num = 0;
	sign = 1;
	has_num = false;
	if (**digit == '-')
	{
		sign = -1;
		(*digit)++;
	}
	else if (**digit == '+')
		(*digit)++;
	while (static_is_digit(**digit))
	{
		has_num = true;
		if (static_is_overflowed(long_num, **digit, sign))
			return (false);
		long_num = long_num * 10 + (**digit - '0');
		(*digit)++;
	}
	return (has_num);
}

static int	static_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	static_is_overflowed(unsigned long long_num, char c, int sign)
{
	if (sign == -1)
		return (long_num > LONG_MAX / 10
			|| (long_num == LONG_MAX / 10 && (c - '0') > 8));
	else
		return (long_num > LONG_MAX / 10
			|| (long_num == LONG_MAX / 10 && (c - '0') > 7));
}
