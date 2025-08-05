/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execution.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:08:43 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/05 19:21:04 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXECUTION_H
# define MSH_EXECUTION_H

# include "lib_ft.h"
# include "lib_dbg.h"
# include "lib_env.h"
# include "lib_gc.h"
# include "lib_msh.h"
# include "msh_builtins.h"

int		msh_execute(t_node *ast_head, t_data *data);
int		msh_execute_cmd(t_node *node, int status, t_env **env, t_gc **gc);
int		msh_execute_pipe(t_node *node, t_data *data);
void	msh_redir_handle(const t_red_node *redir_list);

#endif