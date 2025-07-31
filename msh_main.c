/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:32:51 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/31 11:46:26 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_main.h"

static void	msh_init_data(t_data *share_data)
{
	ft_memset(share_data, 0, sizeof(t_data));
	// Initialize stdin/stdout/stderr if necessary
	// Get terminal attributes if needed
}

int	main(int ac, char **av, char **envp)
{
	t_data	share_data;
	t_env	*env;
	t_gc	*gc;

	(void)ac;
	(void)av;
	msh_init_data(&share_data);
	share_data.envps = envp;
	env = env_initiate(share_data.envps);
	gc = gc_initiate();
	while (true)
	{
		share_data.line = readline("msh$ ");
		if (!share_data.line)
			continue ;
		add_history(share_data.line);
		share_data.token = to_tokens(share_data.line);
		share_data.abs = to_parse(&share_data);
		// if (share_data.err_prs.perr_type
		// msh_handel_parse_error(share_data.err_prs.perr_type, share_data.line); // TODO: handle parse error
		msh_tree_init(share_data.abs, &share_data);
		printf("%d\n", msh_execute_cmd(share_data.abs, share_data.exit_status, &env, &gc));
	}
	return (0);
}
