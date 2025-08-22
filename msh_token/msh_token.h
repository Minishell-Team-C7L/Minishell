/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_token.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:08:44 by aessaber          #+#    #+#             */
/*   Updated: 2025/08/20 22:04:47 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TOKEN_H
# define MSH_TOKEN_H

# include "lib_ft.h"
# include "lib_env.h"
# include "lib_gc.h"
# include "lib_msh.h"

t_token	*to_tokens(t_data *data);
t_token	*ft_fill_tokens(char *line, t_data *data);
int		msh_check_stoken_type(t_token **list_of_t,
			char **token_value, t_data *data);
int		msh_check_ntoken_type(t_token **list_of_t,
			char **token_value, t_data *data);
int		add_token_type(t_token **t_list,
			char **cur_token, t_token_types t_type);
void	free_token_list(t_token **token_list);
void	token_list_add(t_token **list, t_token *new_token);

void	msh_quates_err(t_data *data);
int		msh_is_quote(char c);
int		msh_skip_quates(size_t *i, char *line);
int		msh_is_operator(char *op);

void	skip_whitespace(char **line);
int		is_special_char(char c);

#endif
