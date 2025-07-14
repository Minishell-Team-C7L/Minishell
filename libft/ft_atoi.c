/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdigit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:26:44 by lhchiban          #+#    #+#             */
/*   Updated: 2024/10/25 19:23:19 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	skip_this(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char	*str)
{
	int			i;
	long long	check;
	int			sign;
	long long	returnvalue;

	check = 0;
	i = 0;
	sign = 1;
	returnvalue = 0;
	i = skip_this(str, &sign);
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		returnvalue = returnvalue * 10 + (str[i] - '0');
		if (returnvalue / 10 != check)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		check = returnvalue;
		i++;
	}
	return (returnvalue * sign);
}


