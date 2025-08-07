/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:32:51 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/07 11:55:24 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_main.h"

static void	msh_init_data(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->gc = gc_initiate();
	if (!data->gc)
		exit(dbg_nullarg("gc_initiate"));
	data->env = env_initiate(envp);
	if (!data->env)
	{
		gc_free(&data->gc);
		exit(dbg_nullarg("env_initiate"));
	}
	data->exit_status = 0;
	// Initialize signal handlers here.
	// Initialize stdin/stdout/stderr if necessary
	// Get terminal attributes if needed
}

static void	msh_handel_parse_error(t_data *data)
{
	t_parseerr_type		perr_type;

	perr_type = data->err_prs.perr_type;
	if (perr_type == SYN_E)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		data->exit_status = 258;
		msh_clear_tree(data, &data->abs);
		ft_bzero(&data->err_prs, sizeof(t_parserr));
	}
	else if (perr_type == MEMO_E)
	{
		msh_clear_tree(data, &data->abs);
		ft_bzero(&data->err_prs, sizeof(t_parserr));
	}
}

static void	msh_handel_exit(t_data *mn_data,  int i)
{
	msh_clear_tree(mn_data, &mn_data->abs);
	// clear_history();
	env_list_free(&mn_data->env);
	if (i == 1)
	{
		ft_putstr_fd("exit\n", 2);
		exit(mn_data->exit_status);
	}
}



int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	msh_init_data(&data, envp);
	while (true)
	{
		data.line = readline("msh$ ");
		if (data.line)
			add_history(data.line);
		else
			msh_handel_exit(&data, 1);
		data.token = to_tokens(&data);
		if (!data.token)
			continue ;
		data.abs = to_parse(&data);
		if (!data.err_prs.perr_type)
			msh_tree_init(data.abs, &data);
		else
			msh_handel_parse_error(&data);
		printf("%d\n", msh_execute(data.abs, &data));
	}
	return (msh_handel_exit(&data, 0), data.exit_status);
}
