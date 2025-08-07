/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:26:49 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/07 09:07:27 by lhchiban         ###   ########.fr       */
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
char	*msh_handel_expand(char *args, t_data *data);
char	*msh_dquote_extra(size_t *i, char *args);
bool	msh_variable_is_valid(char exp_c);
void	msh_tree_init(t_node *tree_node, t_data *data);
char 	*msh_skip_emtystr(char *args);
char	*msh_strjoin_and_free(char *str_1, char *str_2);
void	msh_skip_qts(char *res, size_t *i, char *s, size_t *j);
size_t	msh_withoutq_len(char *str);
char	*msh_rm_quates(char *s);

#endif
