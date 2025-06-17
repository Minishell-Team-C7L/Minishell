#ifndef MINISHELL_H
#define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "parse.h"
# include <libc.h>

typedef enum e_token_types
{
    SCMD_T,
    PIPE_T, // |
    REDIR_IN_T, // <
    REDIR_OUT_T, // >
    REDIR_APPEND_T, // >>
    HERE_DOC_T, // <<
    ENV_V_T, // $
    BCMD_T, // exit echo cd ...
}    t_token_types;

typedef struct s_token
{
    t_token_types        type;
    char                *val;
    struct s_token        *prev;
    struct s_token        *next;
}    t_token;

typedef struct s_data // statrt minishell
{
    char     *line;
    t_token *token;
    t_node    *abs;
    t_token *cur_token;
}    t_data;


t_token *to_tokens(char *line);
void    ft_fill_tokens(t_token **list_of_tokens, char *line);
void    check_token_type(t_token **list_of_tokens, char* *line_to_t);
void    add_token_type(t_token **t_list, char **line_ptr, t_token_types t_type);
void    token_list_add(t_token **list, t_token *new_token);

#endif

