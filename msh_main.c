/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:32:51 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/06 07:35:32 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_main.h"

static void	msh_init_data(t_data *share_data)
{
	ft_memset(share_data, 0, sizeof(t_data));
	share_data->env = env_initiate(share_data->envps);
	share_data->gc = gc_initiate();
	// Initialize stdin/stdout/stderr if necessary
	// Get terminal attributes if needed
}

static  void	msh_handel_parse_error(t_data *data)
{
	t_parseerr_type		perr_type;

	perr_type = data->err_prs.perr_type;
	if (perr_type && perr_type == SYN_E)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		data->exit_status = 258;
		msh_clear_tree(data, &data->abs);
		ft_bzero(&data->err_prs, sizeof(t_parserr));
	}
	else if (perr_type && perr_type == MEMO_E)
	{
		msh_clear_tree(data, &data->abs);
		ft_bzero(&data->err_prs, sizeof(t_parserr));
	}
}

static void	msh_handel_exit(t_data *mn_data,  int i)
{
	msh_clear_tree(mn_data, &mn_data->abs);
	// rl_clear_history();
	env_list_free(&mn_data->env);
	if (i == 1)
	{
		ft_putstr_fd("exit\n", 2);
		exit(mn_data->exit_status);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	share_data;

	(void)ac;
	(void)av;
	msh_init_data(&share_data);
	share_data.envps = envp;
	while (true)
	{
		share_data.line = readline("msh$ ");
		if (share_data.line)
			add_history(share_data.line);
		else
			msh_handel_exit(&share_data, 1);
		share_data.token = to_tokens(share_data.line, &share_data);
		if (!share_data.token)
			continue;
		share_data.abs = to_parse(&share_data);
		if (!share_data.err_prs.perr_type)
			msh_tree_init(share_data.abs, &share_data);
		else
			msh_handel_parse_error(&share_data);
		printf("%d\n", msh_execute(share_data.abs, &share_data));
	}
	return (msh_handel_exit(&share_data, 0), share_data.exit_status);
}
