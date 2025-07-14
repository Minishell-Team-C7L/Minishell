
#include "../include/minishell.h"

t_red_type msh_red_type(t_token_types type)
{
    if (REDIR_APPEND_T == type)
        return (APPEND_RED);
    if (REDIR_IN_T == type)
        return (IN_RED);
    if (REDIR_OUT_T == type)
        return (OUT_RED);
    return(HEREDOC_RED);
}

void msh_combine_rediractions(t_red_node *n_red, t_red_node **red_list)
{
    t_red_node *cur_red;

    if (!*red_list)
        *red_list = n_red;//fvd
		return ;
    cur_red = *red_list;
    while(cur_red && cur_red->next)
        cur_red = cur_red->next;
    cur_red->next = n_red;
}

void msh_clear_cmd(t_node *cmd_node)
{
    if (!cmd_node)
        return;
    msh_red_list_clear(&(cmd_node->red_l));
    free(cmd_node->args);
}

void    msh_red_list_clear(t_red_node **red_list)
{
    t_red_node *cur_node;
    t_red_node *next_node;

    next_node = NULL;
    if (!*red_list)
        return ;
    cur_node = *red_list;
    while (cur_node)
    {
        // free(cur_node->val);
        next_node = cur_node->next;
        free(cur_node);
        cur_node = NULL;
        cur_node = cur_node->next;
    }
    *red_list = NULL;
}

int	msh_is_red(t_token_types t_type)
{
	if (t_type == REDIR_APPEND_T || t_type == REDIR_IN_T ||
		t_type == HERE_DOC_T || t_type == REDIR_OUT_T)
		return (1);
	return (0);
}
