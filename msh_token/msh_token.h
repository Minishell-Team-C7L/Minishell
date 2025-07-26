/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_token.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:08:44 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 06:40:08 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TOKEN_H
# define MSH_TOKEN_H

# include "lib_ft.h"
# include "lib_dbg.h"
# include "lib_env.h"
# include "lib_gc.h"
# include "lib_msh.h"

t_token	*to_tokens(char *line);
int		ft_fill_tokens(t_token **list_of_token, char *line);
void	check_token_type(t_token **list_of_t, char **token_value);
void	add_token_type(
			t_token **t_list, char **cur_token, t_token_types t_type);
void	free_token_list(t_token **token_list);
void	token_list_add(t_token **list, t_token *new_token);

char	*ft_rm_whitespaces(char *line);
int		ft_check_quotes(char *line);

int		check_after_op(char *line_err, int line_index);
int		op_calcule(char *line_err, char *operator);
int		ft_line_err(t_token **lst_of_t_err);
int		check_line_errors(char **line);
int		check_line_err(char **line_err);

#endif