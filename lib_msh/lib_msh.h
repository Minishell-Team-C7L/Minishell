/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_msh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:09:59 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/02 10:39:22 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_MSH_H
# define LIB_MSH_H

# include <errno.h>
// For: errno
# include <stdio.h>
// For: perror()
# include <readline/readline.h>
// For: readline()
# include <readline/history.h>
// For: add_history()

# include "lib_ft.h"
# include "lib_dbg.h"
# include "lib_env.h"
# include "lib_gc.h"

typedef enum e_token_types
{
	WORD_T = 1,
	PIPE_T,//			|
	REDIR_IN_T,//		<
	REDIR_OUT_T,//		>
	REDIR_APPEND_T,//	>>
	HERE_DOC_T,//		<<
	ENV_V_T,//			$
	BCMD_T,//			exit echo cd ...
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
	char				*val;//		The filename or delimiter
	t_red_type			type;//		The redirection type
	struct s_red_node	*next;//	Linked list for multiple redirections
}	t_red_node;

typedef struct s_node
{
	struct s_node	*left;
	struct s_node	*right;
	t_node_type		type;
	t_red_node		*red_l;
	t_token			*left_cmd_toknes;
	char			*args;//		Single string containing all arguments
	char			**arg;
}	t_node;

typedef struct s_parserr
{
	t_parseerr_type	perr_type;
}	t_parserr;

typedef struct s_data//				start minishell
{
	char		*line;
	t_token		*token;
	t_node		*abs;
	t_token		*cur_tokens;
	t_parserr	err_prs;
	int			exit_status;
	char		**envps;//			Environment variables
	int			heredoc_intersignal;
}	t_data;

t_env	*msh_env_sort(t_env **env, t_gc **gc);
char	**msh_env_to_array(t_env **env, t_gc **gc);
char	*msh_env_val_parse(const char *value, t_env **env, t_gc **gc);
char	*msh_env_var_parse(const char *variable, t_env **env, t_gc **gc);
void	msh_id_err(const char *arg, const char *cmd);
void	*msh_null_guard(void *ptr, t_env **env, t_gc **gc);
char	*msh_path_get_cmd(const char *cmd, t_env **env, t_gc **gc);
int		msh_perror(const char *cmd_name);
void	msh_quit(int status, t_env **env, t_gc **gc);

#endif