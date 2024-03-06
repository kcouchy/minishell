# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 10:04:34 by kcouchma          #+#    #+#              #
#    Updated: 2024/03/06 10:00:32 by kcouchma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =											\
				Builtins/builtins_utils			\
				Builtins/cd						\
				Builtins/echo					\
				Builtins/env					\
				Builtins/exit					\
				Builtins/export_exec			\
				Builtins/export_parse			\
				Builtins/fenvp_utils			\
				Builtins/pwd					\
				Builtins/unset					\
				Parsing/Lexing/alloc_tables		\
				Parsing/Lexing/check_commands	\
				Parsing/Lexing/check_variables	\
				Parsing/Lexing/lexing_utils		\
				Parsing/Lexing/var_utils		\
				Parsing/Lexing/what_type		\
				Parsing/fill_strings			\
				Parsing/fill_type				\
				Parsing/parsing_to_executing	\
				Parsing/parsing					\
				Pipex/pipex						\
				Pipex/pipex_cmds				\
				Pipex/pipex_utils				\
				Pipex/pipex_exits				\
				Pipex/gnl						\
				Pipex/redirections				\
				Pipex/heredocs					\
				ft_free							\
				minishell						\
				utils							

INC_FILES = -I Pipex/libft

H_FILES =	./Pipex/libft/libft.h				\
			./Pipex/pipex.h						\
			minishell.h

SRC = $(addsuffix .c,$(SRCS))
OBJ = $(addsuffix .o,$(SRCS))

CC = cc
CCFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=20 -g -O0

NAME = minishell

all: $(NAME)

$(NAME) : $(OBJ) $(H_FILES)
	$(MAKE) -C ./Pipex/libft/ bonus
	$(CC) -o $@ $(OBJ) $(CCFLAGS) ./Pipex/libft/libft.a -lreadline

%.o: %.c
	$(CC) -c -o $@ $< $(CCFLAGS) $(INC_FILES)

clean :
	$(MAKE) -C ./Pipex/libft/ clean
	rm -rf $(OBJ)

fclean : clean
	$(MAKE) -C ./Pipex/libft/ fclean
	rm -rf $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
