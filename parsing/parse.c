#include "../include/minishell.h"
#include "../include/parse.h"


int ft_currtoken_pip(t_token *curr_token)
{
    t_token_types curr_type;

    if (!curr_token)
        return(0);
    curr_type = curr_token->type;
    if (curr_type == PIPE_T)
        return (1);
    return (0);

}

void ft_next_token(t_token *curr_token)
{
    curr_token = curr_token -> next;
}

t_node *ft_tree(t_token *curr_token)
{
    t_node *left;
    t_node *right;
    if (!curr_token)
        return (NULL);
    while (curr_token)
    {
        curr_token = curr_token->next;
        if (ft_currtoken_pip(curr_token))
        {
            ft_next_token(curr_token);
            if (!curr_token)
                return (SO_ERROR); // must be error here and go to left
            right = ft_tree(curr_token);
            if (!right)
                return (left);
        }
    }
    return (NULL);
}

t_data *to_parse(t_token *curr_token)
{
    t_data *ast;

    ast->abs = ft_tree(curr_token);
}

