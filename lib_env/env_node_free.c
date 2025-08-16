/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:58:44 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 04:59:10 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_env.h"

void	env_node_free(t_env **env_node)
{
	if (!env_node || !*env_node)
		return ;
	ft_free((void **)&(*env_node)->value);
	ft_free((void **)&(*env_node)->variable);
	ft_free((void **)env_node);
}
