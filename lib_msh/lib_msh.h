/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_msh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:09:59 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/25 11:34:59 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_MSH_H
# define LIB_MSH_H

# include <errno.h>
// For: errno
# include <string.h>
// For: strerror()
# include <stdio.h>
// For: perror(), printf()
# include <readline/readline.h>
// For: readline()
# include <readline/history.h>
// For: add_history()
# include <sys/stat.h>
// For: stat(), S_ISDIR()
# include <signal.h>
// For: sigaction()
# include <termios.h>
// For: termios

// Dependencies:
# include "lib_ft.h"
# include "lib_env.h"
# include "lib_gc.h"

// Macros:
# define PROJECT_NAME "msh"
# define FORK_FAILURE -1
# define IS_CHILD 0

// Enums and Structs:

int	g_sig;

typedef enum e_token_types
{
	WORD_T = 1,
	PIPE_T,
	REDIR_IN_T,
	REDIR_OUT_T,
	REDIR_APPEND_T,
	HERE_DOC_T,
}	t_token_types;

typedef struct s_token
{
	t_token_types	type;
	char			*val;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef enum e_node_type
{
	PIPE_N,
	CMD_N
}	t_node_type;

typedef enum e_parseerr_type
{
	MEMO_E = 1,
	SYN_E
}	t_parseerr_type;

typedef enum e_red_type
{
	IN_RED = 1,
	OUT_RED,
	HEREDOC_RED,
	APPEND_RED
}	t_red_type;

typedef struct s_red_node
{
	char				*val;
	bool				heredoc_exp;
	bool				is_ambiguous;
	t_red_type			type;
	struct s_red_node	*next;
	int					fd;
}	t_red_node;

typedef struct s_node
{
	struct s_node	*left;
	struct s_node	*right;
	t_node_type		type;
	t_red_node		*red_l;
	char			*args;
	char			**arg;
}	t_node;

typedef struct s_parserr
{
	t_parseerr_type	perr_type;
}	t_parserr;

typedef struct s_data
{
	char			*line;
	t_token			*token;
	t_node			*abs;
	t_token			*cur_tokens;
	t_parserr		err_prs;
	int				exit_status;
	char			**envps;
	int				heredoc_count;
	t_list			*heredoc_files;
	t_env			*env;
	t_gc			*gc;
	bool			dollar_exp_state;
	struct termios	original_termios;
	char			*last_cwd;
	bool			is_in_pipe;
	bool			is_white;
	bool			is_onlyqts;
	int				stdin_backup;
	int				stdout_backup;
}	t_data;

void	msh_ctrl_line_off(t_data *data);
void	msh_ctrl_line_on(t_data *data);
void	msh_env_defaults(t_env **env, t_gc **gc);
t_env	*msh_env_sort(t_env **env, t_gc **gc);
char	**msh_env_to_array(t_env **env, t_gc **gc);
char	*msh_env_val_parse(const char *const_value, t_env **env, t_gc **gc);
char	*msh_env_var_parse(const char *variable, t_env **env, t_gc **gc);
void	msh_id_err(const char *arg, const char *cmd);
void	*msh_null_guard(void *ptr, t_env **env, t_gc **gc);
int		msh_path_get_cmd(
			const char *cmd, char **cmd_path, t_env **env, t_gc **gc);
int		msh_perror(const char *cmd_name);
void	msh_print_error(const char *part1, const char *part2);
void	msh_print_fd(const char *str, int fd);
int		msh_puterr(const char *str);
void	msh_quit(t_data *data, int status);
int		msh_signal(void);
int		msh_signal_child(void);
int		msh_signal_off(void);
int		msh_signal_status(int exit_status);

#endif
