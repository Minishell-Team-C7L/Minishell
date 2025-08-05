# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/25 19:56:32 by aessaber          #+#    #+#              #
#    Updated: 2025/08/05 19:30:22 by aessaber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Resources:
#------------------------------------------------------------------------------#

## Output:
NAME		=	minishell

## Directories:
D_OBJS		=	objs_and_deps
D_ROOT		=	.
D_FT		=	lib_ft
D_DBG		=	lib_dbg
D_ENV		=	lib_env
D_GC		=	lib_gc
D_MSH		=	lib_msh
D_BUILTINS	=	msh_builtins
D_EXECUTION	=	msh_execution
D_EXPAND	=	msh_expand
D_PARSE		=	msh_parse
D_TOKEN		=	msh_token

## C Files:
F_MAIN		=	msh_main.c

F_FT		=	ft_atoi.c				\
				ft_calloc.c				\
				ft_free.c				\
				ft_isalnum.c			\
				ft_isalpha.c			\
				ft_isdigit.c			\
				ft_itoa.c				\
				ft_lstlen.c				\
				ft_memcpy.c				\
				ft_memset.c				\
				ft_putchar_err.c		\
				ft_putchar_fd.c			\
				ft_putchar.c			\
				ft_puterr.c				\
				ft_putnbr_fd.c			\
				ft_putstr_fd.c			\
				ft_putstr_nl.c			\
				ft_putstr.c				\
				ft_str_is_mono.c		\
				ft_str_is_num.c			\
				ft_strchr.c				\
				ft_strcmp.c				\
				ft_strcpy.c				\
				ft_strdup.c				\
				ft_strjoin.c			\
				ft_strlcpy.c			\
				ft_strlen.c				\
				ft_strncmp.c			\
				ft_substr.c				\
				ft_wordcount.c

F_DBG		=	dbg_nullarg.c

F_ENV		=	env_get_node.c			\
				env_get_node_prev.c		\
				env_initiate.c			\
				env_list_free.c			\
				env_node_add_back.c		\
				env_node_alloc.c		\
				env_node_del.c			\
				env_node_fill.c			\
				env_node_free.c			\
				env_node_set.c			\
				env_node_update.c		\
				env_sort.c

F_GC		=	gc_env_dup.c			\
				gc_free.c				\
				gc_getcwd.c				\
				gc_initiate.c			\
				gc_malloc.c				\
				gc_split.c				\
				gc_strdup.c				\
				gc_strjoin.c			\
				gc_substr.c

F_MSH		=	msh_env_sort.c			\
				msh_env_to_array.c		\
				msh_env_val_parse.c		\
				msh_env_var_parse.c		\
				msh_id_err.c			\
				msh_null_guard.c		\
				msh_path_get_cmd.c		\
				msh_perror.c			\
				msh_puterr.c			\
				msh_quit.c

F_BUILTINS	=	msh_cd.c				\
				msh_echo.c				\
				msh_env.c				\
				msh_exit.c				\
				msh_export.c			\
				msh_pwd.c				\
				msh_unset.c

F_EXECUTION	=	msh_execute.c			\
				msh_execute_cmd.c		\
				msh_execute_pipe.c		\
				msh_redir_handle.c

F_EXPAND	=	msh_expand_heredoc.c	\
				msh_expand_split_args.c	\
				msh_expand_utils.c		\
				msh_expand.c			\
				msh_tree_init.c

F_PARSE		=	msh_create_and_clean.c	\
				msh_parse_utils_1.c		\
				msh_parse_utils_2.c		\
				msh_parse.c

F_TOKEN		=	msh_linemod.c			\
				msh_linerr.c			\
				msh_token_handel.c

# Compilation:
#------------------------------------------------------------------------------#

## Shell Commands:
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror	\
				-MMD
RM			=	rm -rf

## Source Directories (VPATH):
VPATH		=	$(D_FT)					\
				$(D_DBG)				\
				$(D_ENV)				\
				$(D_GC)					\
				$(D_MSH)				\
				$(D_BUILTINS)			\
				$(D_EXECUTION)			\
				$(D_EXPAND)				\
				$(D_PARSE)				\
				$(D_TOKEN)

## Includes:
INCLUDES	=	-I $(D_ROOT)			\
				-I $(D_FT)				\
				-I $(D_DBG)				\
				-I $(D_ENV)				\
				-I $(D_GC)				\
				-I $(D_MSH)				\
				-I $(D_BUILTINS)		\
				-I $(D_EXECUTION)			\
				-I $(D_EXPAND)			\
				-I $(D_PARSE)			\
				-I $(D_TOKEN)

## Sources & Objects:
S_FT		=	$(addprefix $(D_FT)/, $(F_FT))
S_DBG		=	$(addprefix $(D_DBG)/, $(F_DBG))
S_ENV		=	$(addprefix $(D_ENV)/, $(F_ENV))
S_GC		=	$(addprefix $(D_GC)/, $(F_GC))
S_MSH		=	$(addprefix $(D_MSH)/, $(F_MSH))
S_BUILTINS	=	$(addprefix $(D_BUILTINS)/, $(F_BUILTINS))
S_EXECUTION	=	$(addprefix $(D_EXECUTION)/, $(F_EXECUTION))
S_EXPAND	=	$(addprefix $(D_EXPAND)/, $(F_EXPAND))
S_PARSE		=	$(addprefix $(D_PARSE)/, $(F_PARSE))
S_TOKEN		=	$(addprefix $(D_TOKEN)/, $(F_TOKEN))

SRCS		=	$(F_MAIN)				\
				$(S_FT)					\
				$(S_DBG)				\
				$(S_ENV)				\
				$(S_GC)					\
				$(S_MSH)				\
				$(S_BUILTINS)			\
				$(S_EXECUTION)			\
				$(S_EXPAND)				\
				$(S_PARSE)				\
				$(S_TOKEN)

OBJS_NAMES	=	$(notdir $(SRCS:.c=.o))
OBJS		=	$(addprefix $(D_OBJS)/, $(OBJS_NAMES))
DEPS		=	$(OBJS:.o=.d)

# Rules:
#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

$(D_OBJS):
	@mkdir -p $(D_OBJS)

$(D_OBJS)/%.o: %.c | $(D_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(D_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)