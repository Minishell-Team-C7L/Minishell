#include "../include/minishell.h"

t_token *to_tokens(char *line)
{
	t_token *list_of_tokens;

	ft_fill_tokens(&list_of_tokens , line);
	free(line);
	return(list_of_tokens);
}

void	ft_fill_tokens(t_token **list_of_token, char *line)
{
	while (*line)
	{
		while(*line == ' ' || *line == '\t')
			line++;
		if(*line == '>' ||  *line == '<' || *line == '|' ||
			*line == '&' ||  *line == '(' || *line == ')')
		{
			check_token_type(list_of_token, &line);
			line++;
		}
	}
}

void	check_token_type(t_token **list_of_t, char **token_value)
{
	if (!ft_strncmp(*token_value, "|", 1))
		add_token_type(list_of_t, token_value, PIPE_T);
	if (!ft_strncmp(*token_value, "<<", 2))
		add_token_type(list_of_t, token_value, HERE_DOC_T);
	else if (!ft_strncmp(*token_value, ">>", 2))
		add_token_type(list_of_t, token_value, REDIR_APPEND_T);
	else if (!ft_strncmp(*token_value, "<", 1))
		add_token_type(list_of_t, token_value, REDIR_IN_T);
	else if (!ft_strncmp(*token_value, ">", 1))
		add_token_type(list_of_t, token_value, REDIR_OUT_T);
}

void	add_token_type(t_token **t_list, char **cur_token, t_token_types t_type)
{
	t_token *new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return ;
	new_token->type = t_type;
	new_token->val = *cur_token; // her we have the adresse of the cur token in the line
	token_list_add(t_list, new_token);
	if (t_type == REDIR_APPEND_T || t_type == HERE_DOC_T)
		*cur_token +=2;
	else
		*cur_token +=1;
	return ;
}

void	token_list_add(t_token **list, t_token *new_token)
{
	t_token *curr_list;

	if (!*list)
	{
		*list = new_token;
		return;
	}
	curr_list = *list; // curr_list pointer to the first list elements
	while (curr_list && curr_list->next)
		curr_list = curr_list->next;
	curr_list->next = new_token;
	new_token -> prev = curr_list;
}
