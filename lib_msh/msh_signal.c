/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 08:32:31 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/18 07:03:24 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_msh.h"

static void	static_signal_ctrl_c(int sig);

int	msh_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = static_signal_ctrl_c;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (msh_perror("sigaction"));
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (msh_perror("sigaction"));
	return (EXIT_SUCCESS);
}

static void	static_signal_ctrl_c(int sig)
{
	g_sig = sig;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
