/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:26:49 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 04:54:05 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXPAND_H
# define MSH_EXPAND_H

# include "lib_ft.h"
# include "lib_dbg.h"
# include "lib_env.h"
# include "lib_gc.h"
# include "lib_msh.h"

void	msh_expand_heredoc(int fd, char *read_line, t_data *data);
char	**msh_expand_split_args(char const *arg);
char	**msh_handel_expand(char *args, t_data *data);
char	*msh_dquote_extra(size_t *i, char *args);
bool	msh_variable_is_valid(char exp_c);
void	msh_tree_init(t_node *tree_node, t_data *data);

#endif