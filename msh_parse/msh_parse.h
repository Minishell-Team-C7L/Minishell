/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:08:58 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 15:33:39 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PARSE_H
# define MSH_PARSE_H

# include "lib_ft.h"
# include "lib_dbg.h"
# include "lib_env.h"
# include "lib_gc.h"
# include "lib_msh.h"
# include "msh_token.h"
# include "msh_expand.h"

t_node		*msh_head_combine(t_data *cur_data, t_node *left, t_node *right);
t_node		*msh_new_node(t_node_type n_type);
t_node		*msh_new_cmd_node(void);
t_red_node	*msh_new_red_node(char *value, t_token_types t_type, t_data *data);
int			msh_add_arg_to_string(char **args, char *value);
int			msh_build_args_string(char **args, t_data *cur_data);
int			msh_build_cmd_with_args(t_data *cur_data, char **args);
void		msh_clear_cmd(t_node *cmd_node);
void		msh_free_cmd_args(t_node *cmd_node);
void		msh_free_args_string(char **args);
bool		msh_red_list(t_data *cur_data, t_red_node **red_list);
void		msh_clear_tree_rec(t_node *tree);

t_red_type	msh_red_type(t_token_types type);
void		msh_combine_rediractions(t_red_node *n_red, t_red_node **red_list);
void		msh_clear_tree(t_data *cur_data, t_node **tree);
void		msh_red_list_clear(t_red_node **red_list);
int			msh_is_red(t_data *data, t_token_types t_type);
bool		msh_check_heredoc(char *delimiter);
bool		msh_herdocdel_isdigit(char *del_val);

int			msh_currtoken_pip(t_token *curr_token);
t_node		*msh_tree(t_data *data);
t_node		*to_parse(t_data *data);
t_node		*before_pip(t_data *cur_data);

char	*msh_heredoc_chval(char *del);
bool	msh_dollar_sign(char *delimeter);

#endif
