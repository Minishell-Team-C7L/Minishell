# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 13:33:04 by aessaber          #+#    #+#              #
#    Updated: 2025/05/05 03:17:33 by aessaber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Shell_Commands:
CC          =   cc
FLAGS       =   -Wall -Wextra -Werror
RM          =   rm -f

# Files:
NAME        =   minishell
ROOT        =   mandetory
HEADERS     =   $(ROOT_B)/msh_header.h
FUNCS       =   msh_main.c   \
                
FILES       =   $(addprefix $(ROOT)/, $(FUNCS))
OBJS        =   $(FILES:.c=.o)

# Files_Bonus:
BONUS       =   minishell_bonus
ROOT_B      =   mandetory
HEADERS_B   =   $(ROOT_B)/msh_header.h
FUNCS_B     =   mshh_main.c   \
                
FILES_B     =   $(addprefix $(ROOT_B)/, $(FUNCS_B))
OBJS_B      =   $(FILES_B:.c=.o)