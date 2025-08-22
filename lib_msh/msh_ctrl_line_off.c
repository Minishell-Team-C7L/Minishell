/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ctrl_line_off.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:04:28 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/22 09:22:40 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

void	msh_ctrl_line_off(t_data *data)
{
	struct termios	new_termios;

	if (tcgetattr(STDIN_FILENO, &data->original_termios) == -1)
	{
		msh_perror("tcgetattr");
		msh_quit(data, EXIT_FAILURE);
	}
	new_termios = data->original_termios;
	new_termios.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
	{
		msh_perror("tcsetattr");
		msh_quit(data, EXIT_FAILURE);
	}
}
