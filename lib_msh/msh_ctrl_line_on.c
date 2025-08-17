/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ctrl_line_on.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:05:46 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/17 12:08:57 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

void	msh_ctrl_line_on(t_data *data)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &data->original_termios) == -1)
		msh_perror("tcsetattr");
}
