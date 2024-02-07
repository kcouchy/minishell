# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 10:04:34 by kcouchma          #+#    #+#              #
#    Updated: 2024/02/07 14:38:20 by kcouchma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =										\
				Pipex/bonus_pipex			\
				Pipex/bonus_cmds			\
				Pipex/utils					\
				Pipex/errors				\
				Pipex/single_cmd			\
				Parsing/parsing				\
				Builtins/cd					\
				Builtins/echo				\
				Builtins/env				\
				Builtins/exit				\
				Builtins/export				\
				Builtins/pwd				\
				main						

INC_FILES = -I Pipex/libft

SRC = $(addsuffix .c,$(SRCS))
OBJ = $(addsuffix .o,$(SRCS))

CC = cc
CCFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=20 -g

NAME = minishell

all: $(NAME)

$(NAME) : $(OBJ)
	$(MAKE) -C ./Pipex/libft/ bonus
	$(CC) -o $@ $(OBJ) ./Pipex/libft/libft.a -lreadline

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
