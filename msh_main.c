/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:32:51 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/23 21:14:21 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_main.h"

static void	msh_init_data(t_data *data, char **envps);
static int	static_minishell(t_data *data);
static void	msh_handel_parse_error(t_data *data);
static void	msh_handel_exit(t_data *data, int i);

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	((void)ac, (void)av);
	if (!isatty(1) || !isatty(0))
		return (2);
	msh_init_data(&data, envp);
	while (true)
	{
		(msh_signal(), msh_ctrl_line_off(&data));
		data.line = readline("msh$ ");
		if (g_sig == SIGINT)
		{
			data.exit_status = EXIT_FAILURE;
			g_sig = 0;
		}
		if (!data.line)
			msh_handel_exit(&data, 1);
		if (data.line[0])
			add_history(data.line);
		if (static_minishell(&data) == EXIT_FAILURE)
			continue ;
		data.exit_status = msh_execute(&data, data.abs);
		(msh_clear_tree(&data, &data.abs), msh_ctrl_line_on(&data));
	}
	return (msh_handel_exit(&data, 0), data.exit_status);
}

static void	msh_init_data(t_data *data, char **envps)
{
	ft_memset(data, 0, sizeof(t_data));
	data->envps = envps;
	data->env = env_initiate(data->envps);
	data->gc = gc_initiate();
	msh_env_defaults(&data->env, &data->gc);
	if (msh_signal() == EXIT_FAILURE)
		msh_quit(data, EXIT_FAILURE);
}

static int	static_minishell(t_data *data)
{
	data->token = to_tokens(data);
	if (!data->token || data->is_white)
		return (EXIT_FAILURE);
	data->abs = to_parse(data);
	if (data->err_prs.perr_type)
	{
		msh_handel_parse_error(data);
		return (EXIT_FAILURE);
	}
	msh_tree_init(data, data->abs);
	if (data->heredoc_count > 16)
	{
		msh_puterr("msh: maximum here-document count exceeded\n");
		msh_quit(data, 2);
	}
	if (msh_handle_heredocs(data, data->abs) != EXIT_SUCCESS)
	{
		data->exit_status = EXIT_FAILURE;
		msh_clear_tree(data, &data->abs);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	msh_handel_parse_error(t_data *data)
{
	t_parseerr_type		perr_type;

	perr_type = data->err_prs.perr_type;
	if (perr_type == SYN_E)
	{
		msh_print_error("syntax error", NULL);
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

static void	msh_handel_exit(t_data *data, int i)
{
	msh_clear_tree(data, &data->abs);
	rl_clear_history();
	env_list_free(&data->env);
	if (i == 1)
	{
		msh_print_fd("exit", 2);
		exit(data->exit_status);
	}
}
