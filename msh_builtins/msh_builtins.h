/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:03:25 by aessaber          #+#    #+#             */
/*   Updated: 2025/07/26 06:55:00 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_BUILTINS_H
# define MSH_BUILTINS_H

# include <stdint.h>
// For: uint8_t

# include "lib_ft.h"
# include "lib_dbg.h"
# include "lib_env.h"
# include "lib_gc.h"
# include "lib_msh.h"

typedef enum e_cd_type
{
	CD_ARG,
	CD_HOME,
	CD_OLDPWD,
	CD_EMPTY
}	t_cd_type;

typedef struct s_cd
{
	t_env		*env_oldpwd;
	t_env		*env_home;
	char		*oldpwd;
	char		*pwd;
	char		*path;
	t_cd_type	type;
}	t_cd;

typedef struct s_echo
{
	int		arg;
	bool	flag_n;
}	t_echo;

int	msh_cd(const char **arg, t_env **env, t_gc **gc);
int	msh_echo(const char **arg);
int	msh_env(t_env *env);
int	msh_exit(const char **arg, int status, t_env **env, t_gc **gc);
int	msh_export(const char **arg, t_env **env, t_gc **gc);
int	msh_pwd(t_gc **gc);
int	msh_unset(const char **arg, t_env **env);

#endif