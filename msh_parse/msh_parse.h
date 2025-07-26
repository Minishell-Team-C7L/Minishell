/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:08:58 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 06:36:28 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PARSE_H
# define MSH_PARSE_H

# include "lib_ft.h"
# include "lib_dbg.h"
# include "lib_env.h"
# include "lib_gc.h"
# include "lib_msh.h"

t_node		*msh_head_combine(t_data *cur_data, t_node *left, t_node *right);
t_node		*msh_new_node(t_node_type n_type);
t_node		*msh_new_cmd_node(void);
t_red_node	*msh_new_red_node(t_token_types t_type);
int			msh_add_arg_to_string(char **args, char *value);
int			msh_build_args_string(char **args, t_data *cur_data);
t_node		*msh_build_cmd_with_args(t_data *cur_data);
void		msh_free_cmd_args(t_node *cmd_node);
void		msh_free_args_string(char **args);
bool		msh_red_list(t_data *cur_data, t_red_node **red_list);

t_red_type	msh_red_type(t_token_types type);
void		msh_combine_rediractions(t_red_node *n_red, t_red_node **red_list);
void		msh_clear_cmd(t_node *cmd_node);
void		msh_red_list_clear(t_red_node **red_list);
int			msh_is_red(t_token_types t_type);

int			msh_currtoken_pip(t_token *curr_token);
void		msh_next_token(t_data *cur_data);
t_node		*msh_tree(t_data *data);
t_node		*to_parse(t_data *data);
t_node		*before_pip(t_data *cur_data);

#endif