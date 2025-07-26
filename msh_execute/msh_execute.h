/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:08:43 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 04:53:22 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXECUTE_H
# define MSH_EXECUTE_H

# include "lib_ft.h"
# include "lib_dbg.h"
# include "lib_env.h"
# include "lib_gc.h"
# include "lib_msh.h"
# include "msh_builtins.h"

# define CMD_NOT_FOUND 127

int	msh_execute_cmd(
		const char **arg, int status, t_env **env, t_gc **gc);

#endif