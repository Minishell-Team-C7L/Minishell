#ifndef MINISHELL_H
#define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "parse.h"
# include <libc.h>
# include <stdbool.h>

typedef enum e_token_types
{
    WORD_T,
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
	IN_RED,
	OUT_RED,
	HEREDOC_RED,
	APPEND_RED
}	t_red_type;

typedef struct s_red_node
{
	char				*val;      // The filename or delimiter
	t_red_type			type;        // The redirection type
	struct s_red_node	*next;       // Linked list for multiple redirections
}	t_red_node;

// typedef struct s_io_node
// {
// 	t_io_type			type;
// 	char				*value;
// 	struct s_io_node	*next;
// }	t_io_node;

typedef struct s_node
{
	char				*args;// arr of strings
	struct s_node		*left;
	struct s_node		*right;
	t_node_type			type;
    t_red_node          *red_l;
	t_token				*left_cmd_toknes;
}	t_node;

typedef struct s_parserr
{
	t_parseerr_type perr_type;
}	t_parserr;


typedef struct s_data // statrt minishell
{
    char     *line;
    t_token *token;
    t_node    *abs;
    t_token *cur_tokens;
	t_parserr err_prs;
}    t_data;

int 	ft_line_err(t_token **lst_of_t_err);
char 	*ft_rm_whitespaces(char *line);
t_token *to_tokens(char *line);
char	*ft_strdup(const char *s1);
int    	ft_fill_tokens(t_token **list_of_tokens, char *line);
void    check_token_type(t_token **list_of_tokens, char* *line_to_t);
void    add_token_type(t_token **t_list, char **line_ptr, t_token_types t_type);
void    token_list_add(t_token **list, t_token *new_token);
int 	ft_check_quotes(char *line);
t_node *msh_head_combine(t_data *cur_data ,t_node *left, t_node *right);
t_node 	*msh_tree(t_data *data);
int	msh_join_args(char **args, t_data *cur_data);
char *msh_join_args_sp(const char *token_val, const char *arg, char *sp);
t_node *msh_new_node(t_node_type n_type);
bool msh_red_list(t_data *cur_data, t_red_node **red_list);
t_red_type msh_red_type(t_token_types type);
void msh_combine_rediractions(t_red_node *n_red, t_red_node **red_list);
void msh_clear_cmd(t_node *cmd_node);
void    msh_red_list_clear(t_red_node **red_list);
t_node *before_pip(t_data *cur_data);
t_node *to_parse(t_data *data);
void msh_next_token(t_data *cur_data);
int msh_currtoken_pip(t_token *curr_token);
t_red_node *msh_new_red_node(t_token_types t_type);
int	msh_is_red(t_token_types t_type);

#endif


// typedef enum e_t_types
// {
//     WORD_T,
//     PIPE_T, // |
//     REDIR_IN_T, // <
//     REDIR_OUT_T, // >
//     REDIR_APPEND_T, // >>
//     HERE_DOC_T, // <<
//     ENV_V_T, // $
//     BCMD_T, // exit echo cd ...
// } t_t_type;

// typedef struct s_token
// {
//   t_t_type type;
//   char *val;
//   struct s_token *prev;
//   struct s_token *next;
// } t_token;

// typedef enum e_n_type
// {
//   PIP_N,
//   CMD_N
// } t_n_type;

// typedef struct s_node
// {
//   t_n_type type;
//   char *arg;
//   struct s_node *left;
//   struct s_node *right;
//   t_token *left_cmd_t;
// } t_node;

// typedef enum s_p_err
// {
//   MEM_E = 1
// } t_p_err;

// typedef struct s_data
// {
//     char *line;
//     t_token *token;
//     t_node *ab;
//     t_p_err type;
// } t_data;

// t_node *to_parse(t_data *data)
// {
//   return 0;
// }
// int main() {
//   t_data s_data;

//   s_data.line = "ls | ls";
//   while (*(s_data).line)
//   {
//     if (*(s_data).line != '|')
//     {
//       s_data.token->type = PIPE_T;
//       s_data.token->val = &(s_data).line;
//       s_data.line++;
//     }
//     else if (*(s_data).line != ' ')
//     {
//       s_data.token->type = WORD_T;
//       while (*(s_data).line && *(s_data).line != ' ')
//         s_data.token->val = *(s_data).line++;
//     }
//     s_data.token->prev = s_data.token;
//     s_data.token = s_data.token->next;
//     // s_data.token->next = NULL;
//   }
//   to_parse(&s_data.ab);
//   return 0;
// }
