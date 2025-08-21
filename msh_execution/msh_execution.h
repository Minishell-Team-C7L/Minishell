/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execution.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:08:43 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 22:33:03 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXECUTION_H
# define MSH_EXECUTION_H

# include "lib_ft.h"
# include "lib_env.h"
# include "lib_gc.h"
# include "lib_msh.h"
# include "msh_builtins.h"
# include "msh_expand.h"

int		msh_execute(t_data *data, t_node *ast_head);
int		msh_execute_cmd(t_data *data, int status, t_env **env, t_gc **gc);
int		msh_execute_pipe(t_node *node, t_data *data);
int		msh_handle_heredocs(t_data *data, t_node *node);
void	msh_handle_redir(const t_red_node *redir_list);
void	msh_handle_tree_heredocs(t_data *data, t_node *node);

#endif