#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

// typedef enum e_parseerr_type
// {
// 	SYNTAX_E
// }	t_parseerr_type;

int pars_err(void);
int check_line_err(char **line_err);
int op_calcule(char *line_err, char *operator);
// int ft_currtoken_pip(t_token *curr_token);
// void ft_next_token(t_token *curr_token);
// t_node *ft_tree(t_token *curr_token);
// t_node *to_parse(t_token *curr_token);
// t_node *before_pip(t_token *left_of_pip);
// int ft_currtoken_pip(t_token *curr_token);

#endif
