/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_gc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:07:59 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 04:32:29 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_GC_H
# define LIB_GC_H

# include "lib_ft.h"
# include "lib_dbg.h"
# include "lib_env.h"

typedef struct s_alloc
{
	void			*ptr;
	struct s_alloc	*next;
}	t_alloc;

typedef struct s_gc
{
	t_alloc	*head;
}	t_gc;

t_env	*gc_env_dup(t_env **env, t_gc **gc);
void	gc_free(t_gc **gc);
void	*gc_getcwd(t_gc **gc);
void	*gc_malloc(size_t size, t_gc **gc);
char	**gc_split(const char *str, char delimiter, t_gc **gc);
char	*gc_strdup(const char *s1, t_gc **gc);
char	*gc_strjoin(char const *str_1, char const *str_2, t_gc **gc);
char	*gc_substr(char const *str, unsigned int start, size_t len, t_gc **gc);

#endif