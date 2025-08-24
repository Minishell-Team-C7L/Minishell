/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 08:18:13 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/24 18:21:15 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

static void	static_unlink(void *file_name)
{
	if (file_name)
		unlink((const char *)file_name);
}

void	msh_quit(t_data *data, int status)
{
	if (!data)
		exit(status);
	if (data->heredoc_files)
		ft_lstiter(data->heredoc_files, &static_unlink);
	if (data->env)
		env_list_free(&data->env);
	if (data->gc)
		gc_free(&data->gc);
	exit(status);
}
