/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:36:06 by lhchiban          #+#    #+#             */
/*   Updated: 2025/08/17 19:43:11 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

bool msh_herdocdel_isdigit(char *del_val)
{
	int i;

	i = -1;
	while(del_val[++i])
		if (!ft_isdigit(del_val[i]))
			return (false);
	return (true);
}
