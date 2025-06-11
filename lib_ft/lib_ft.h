/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_library.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:51:26 by aessaber          #+#    #+#             */
/*   Updated: 2025/05/21 19:48:06 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_FT_H
# define LIB_FT_H

# include "minishell.h"

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_puterr(char *str);
bool	ft_str_is_mono(char *str, char constant, size_t start);
int		ft_lstlen(t_list *lst);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

#endif