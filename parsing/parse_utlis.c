
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:40:33 by lhchiban          #+#    #+#             */
/*   Updated: 2025/07/13 18:43:20 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * msh_head_combine - Creates a new pipe node combining left and right branches
 * @cur_data: Current parsing data structure containing error information
 * @left: Left child node (command before pipe)
 * @right: Right child node (command after pipe)
 * 
 * Returns: New pipe node on success, NULL on failure
 * Sets memory error in cur_data on allocation failure
 */
t_node *msh_head_combine(t_data *cur_data ,t_node *left, t_node *right)
{
        t_node *head_node;

        head_node = msh_new_node(PIPE_N);
        if (!head_node)
                return (cur_data->err_prs.perr_type = MEMO_E ,NULL);
        head_node->left = left;
        head_node->right = right;
        return (head_node);
}

/*
 * msh_new_node - Allocates and initializes a new AST node
 * @n_type: Type of node to create (PIPE_N or CMD_N)
 * 
 * Returns: Newly allocated node on success, NULL on failure
 * Initializes all fields to zero/NULL using ft_calloc
 */
t_node *msh_new_node(t_node_type n_type)
{
        t_node          *new_node;

        new_node = (t_node *)ft_calloc(1, sizeof(t_node));
        if (!new_node)
                return (NULL);
        new_node->type = n_type;
        return (new_node);
}

/*
 * msh_new_cmd_node - Allocates a new command node with space for arguments
 * @arg_count: Number of arguments to allocate space for
 * 
 * Returns: Newly allocated command node on success, NULL on failure
 * Allocates extra space for the flexible array member args[]
 */
t_node *msh_new_cmd_node(int arg_count)
{
        t_node          *new_node;
        size_t          total_size;

        total_size = sizeof(t_node) + (arg_count + 1) * sizeof(char *);
        new_node = (t_node *)ft_calloc(1, total_size);
        if (!new_node)
                return (NULL);
        new_node->type = CMD_N;
        return (new_node);
}

/*
 * msh_new_red_node - Creates a new redirection node
 * @t_type: Token type to convert to redirection type
 * 
 * Returns: New redirection node on success, NULL on failure
 * Initializes val to NULL and converts token type to redirection type
 */
t_red_node *msh_new_red_node(t_token_types t_type)
{
        t_red_node *red_n_node;

        red_n_node = (t_red_node *)ft_calloc(1, sizeof(t_red_node));
        if (!red_n_node)
                return NULL;
        red_n_node->val = ft_strdup(NULL);
        red_n_node->type = msh_red_type(t_type);
        if (!red_n_node->type)
                return(free(red_n_node), NULL);
        return (red_n_node);
}

/*
 * msh_count_args_tokens - Counts consecutive WORD tokens for array allocation
 * @cur_data: Current parsing data with token position
 * 
 * Returns: Number of consecutive WORD tokens from current position
 * Does not modify current token position, only counts for sizing
 */
int     msh_count_args_tokens(t_data *cur_data)
{
        t_token *temp_token;
        int             count;

        count = 0;
        temp_token = cur_data->cur_tokens;
        while (temp_token && temp_token->type == WORD_T)
        {
                count++;
                temp_token = temp_token->next;
        }
        return (count);
}

/*
 * msh_add_arg_to_array - Adds a string argument to the args array at index
 * @args: Pointer to the arguments array
 * @index: Index where to place the new argument
 * @value: String value to duplicate and store
 * 
 * Returns: 1 on success, 0 on allocation failure
 * Creates a duplicate of value to store in the array
 */
int     msh_add_arg_to_array(char ***args, int index, char *value)
{
        (*args)[index] = ft_strdup(value);
        if (!(*args)[index])
                return (0);
        return (1);
}

/*
 * msh_build_args_array - Builds array of arguments from consecutive WORD tokens
 * @args: Pointer to store the allocated arguments array
 * @cur_data: Current parsing data containing tokens and error info
 * 
 * Returns: 1 on success, 0 on failure
 * Allocates array based on token count, fills with duplicated token values
 * Sets memory error in cur_data on allocation failure
 */
int     msh_build_args_array(char ***args, t_data *cur_data)
{
        int     count;
        int     i;

        *args = NULL;
        count = msh_count_args_tokens(cur_data);
        if (count == 0)
                return (1);
        *args = ft_calloc(count + 1, sizeof(char *));
        if (!*args)
                return (cur_data->err_prs.perr_type = MEMO_E, 0);
        i = 0;
        while (cur_data->cur_tokens && cur_data->cur_tokens->type == WORD_T)
        {
                if (!msh_add_arg_to_array(args, i, cur_data->cur_tokens->val))
                {
                        msh_free_args_array(args);
                        return (cur_data->err_prs.perr_type = MEMO_E, 0);
                }
                i++;
                msh_next_token(cur_data);
        }
        return (1);
}

/*
 * msh_build_cmd_with_args - Builds a command node with arguments from tokens
 * @cur_data: Current parsing data containing tokens and error info
 * 
 * Returns: New command node with args filled, NULL on failure
 * Allocates command node with proper size for flexible array member
 */
t_node *msh_build_cmd_with_args(t_data *cur_data)
{
        int             count;
        int             i;
        t_node  *cmd_node;

        count = msh_count_args_tokens(cur_data);
        cmd_node = msh_new_cmd_node(count);
        if (!cmd_node)
                return (cur_data->err_prs.perr_type = MEMO_E, NULL);
        
        i = 0;
        while (cur_data->cur_tokens && cur_data->cur_tokens->type == WORD_T)
        {
                cmd_node->args[i] = ft_strdup(cur_data->cur_tokens->val);
                if (!cmd_node->args[i])
                {
                        msh_free_cmd_args(cmd_node);
                        free(cmd_node);
                        return (cur_data->err_prs.perr_type = MEMO_E, NULL);
                }
                i++;
                msh_next_token(cur_data);
        }
        cmd_node->args[i] = NULL;
        return (cmd_node);
}

/*
 * msh_free_cmd_args - Frees all argument strings in a command node
 * @cmd_node: Command node containing args to free
 * 
 * Frees each individual string in the flexible array member args[]
 * Does not free the node itself, only the argument strings
 */
void msh_free_cmd_args(t_node *cmd_node)
{
        int i;

        if (!cmd_node)
                return;
        i = 0;
        while (cmd_node->args[i])
        {
                free(cmd_node->args[i]);
                i++;
        }
}

/*
 * msh_free_args_array - Frees the arguments array and all its strings
 * @args: Pointer to the arguments array to free
 * 
 * Frees each individual string in the array, then the array itself
 * Sets the pointer to NULL after freeing to prevent double-free
 */
void    msh_free_args_array(char ***args)
{
        int     i;

        if (!args || !*args)
                return ;
        i = 0;
        while ((*args)[i])
        {
                free((*args)[i]);
                i++;
        }
        free(*args);
        *args = NULL;
}

/*
 * msh_red_list - Parses and builds linked list of redirections
 * @cur_data: Current parsing data with tokens and error info
 * @red_list: Pointer to store the built redirection list
 * 
 * Returns: true on success, false on failure
 * Processes consecutive redirection tokens, expects WORD after each operator
 * Sets syntax error if WORD token missing after redirection operator
 */
bool msh_red_list(t_data *cur_data, t_red_node **red_list)
{
        t_red_node *red_node;

        *red_list = NULL;
        while (cur_data->cur_tokens && msh_is_red(cur_data->cur_tokens->type))
        {
                red_node = msh_new_red_node(cur_data->cur_tokens->type);
                if (!red_node)
                        return (cur_data->err_prs.perr_type = MEMO_E, false);
                msh_next_token(cur_data);
                if (!cur_data->cur_tokens || cur_data->cur_tokens->type != WORD_T)
                        return (cur_data->err_prs.perr_type = SYN_E, false);
                red_node->val = ft_strdup(cur_data->cur_tokens->val);
                if (!red_node->val)
                        return (cur_data->err_prs.perr_type = MEMO_E, false);
                msh_combine_rediractions(red_node, red_list);
                msh_next_token(cur_data);
        }
        return (true);
}
