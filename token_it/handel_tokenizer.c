#include "../include/minishell.h"
#include "../include/parse.h"
#include <stdio.h>

t_token *to_tokens(char *line)
{
        t_token *list_of_tokens;

        list_of_tokens = NULL;
        line = ft_rm_whitespaces(line);
        ft_fill_tokens(&list_of_tokens , line);
        // free(line);
        return(list_of_tokens);
}

static int      is_special_char(char c)
{
        return (c == '>' || c == '<' || c == '|' || c == '&' ||
                        c == '\'' || c == '\"');
}

static void     skip_whitespace(char **line)
{
        while (**line > 0 && **line <= 32)
                (*line)++;
}

int     ft_fill_tokens(t_token **list_of_token, char *line)
{
        while (*line)
        {
                skip_whitespace(&line);
                if (is_special_char(*line))
                {
                        if (!*++line)
                                return (ft_line_err(list_of_token));
                        line--;
                        if (check_line_err(&line) && *line != '&')
                                check_token_type(list_of_token, &line);
                        else
                                return (ft_line_err(list_of_token));
                }
                else
                        check_token_type(list_of_token, &line);
        }
        return (0);
}

void    check_token_type(t_token **list_of_t, char **token_value)
{
        if (!ft_strncmp(*token_value, "|", 1))
                add_token_type(list_of_t, token_value, PIPE_T);
        else if (!ft_strncmp(*token_value, "<<", 2))
                add_token_type(list_of_t, token_value, HERE_DOC_T);
        else if (!ft_strncmp(*token_value, ">>", 2))
                add_token_type(list_of_t, token_value, REDIR_APPEND_T);
        else if (!ft_strncmp(*token_value, "<", 1))
                add_token_type(list_of_t, token_value, REDIR_IN_T);
        else if (!ft_strncmp(*token_value, ">", 1))
                add_token_type(list_of_t, token_value, REDIR_OUT_T);
        else
                add_token_type(list_of_t, token_value, WORD_T);
}

static int      handle_quoted_word(char **cur_token, char **start)
{
        char    quote;
        int             len;

        quote = **cur_token;
        (*cur_token)++;
        *start = *cur_token;
        while (**cur_token && **cur_token != quote)
                (*cur_token)++;
        len = *cur_token - *start;
        if (**cur_token == quote)
                (*cur_token)++;
        return (len);
}

static int      handle_regular_word(char **cur_token, char *start)
{
        while (**cur_token && **cur_token != ' ' && **cur_token > 32 &&
                   **cur_token != '|' && **cur_token != '<' && **cur_token != '>')
                (*cur_token)++;
        return (*cur_token - start);
}

static int      get_token_length(char **cur_token, char **start, t_token_types t_type)
{
        *start = *cur_token;
        if (t_type == REDIR_APPEND_T || t_type == HERE_DOC_T)
        {
                (*cur_token) += 2;
                return (2);
        }
        else if (t_type == WORD_T)
        {
                if (**cur_token == '\'' || **cur_token == '\"')
                        return (handle_quoted_word(cur_token, start));
                else
                        return (handle_regular_word(cur_token, *start));
        }
        else
        {
                (*cur_token)++;
                return (1);
        }
}

void    add_token_type(t_token **t_list, char **cur_token, t_token_types t_type)
{
        t_token *new_token;
        char    *start;
        int             len;

        new_token = (t_token *)ft_calloc(1, sizeof(t_token));
        if (!new_token)
                return ;
        new_token->type = t_type;
        len = get_token_length(cur_token, &start, t_type);
        new_token->val = ft_calloc(len + 1, sizeof(char));
        if (!new_token->val)
        {
                free(new_token);
                return ;
        }
        ft_memcpy(new_token->val, start, len);
        new_token->val[len] = '\0';
        token_list_add(t_list, new_token);
}

void    free_token_list(t_token **token_list)
{
        t_token *current;
        t_token *next;

        if (!token_list || !*token_list)
                return ;
        current = *token_list;
        while (current)
        {
                next = current->next;
                if (current->val)
                        free(current->val);
                free(current);
                current = next;
        }
        *token_list = NULL;
}

void    token_list_add(t_token **list, t_token *new_token)
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
        new_token->prev = curr_list;
}
