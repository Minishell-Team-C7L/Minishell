/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:42 by aessaber          #+#    #+#             */
/*   Updated: 2025/06/02 14:38:47 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

# include "lib_ft.h"
# include "lib_gc.h"
# include "lib_env.h"
# include "lib_msh.h"
# include "msh_builtins.h"

#endif
/* Rules:
- Funcitons made specifically for minishell should start with "msh_"
- Functions that are useful outside minishell should start with "ft_" 
*/