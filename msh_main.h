/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_main.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:42 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 04:51:11 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_MAIN_H
# define MSH_MAIN_H

# include <readline/readline.h>
# include <readline/history.h>

# include "lib_ft.h"
# include "lib_dbg.h"
# include "lib_env.h"
# include "lib_gc.h"
# include "lib_msh.h"
# include "msh_builtins.h"
# include "msh_execute.h"
# include "msh_expand.h"
# include "msh_parse.h"
# include "msh_token.h"

#endif
/* Rules:
- Funcitons made specifically for minishell should start with "msh_"
- Garbage collector functions should start "gc_"
- Other functions that are useful outside minishell should start with "ft_"
*/