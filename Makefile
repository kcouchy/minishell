# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lribette <lribette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 10:04:34 by kcouchma          #+#    #+#              #
#    Updated: 2024/02/05 12:14:14 by lribette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =										\
				Pipex/bonus_pipex			\
				Pipex/bonus_cmds			\
				Pipex/utils					\
				Pipex/errors				\
				Parsing/alloc_tables		\
				Parsing/check_commands		\
				Parsing/count_types			\
				Parsing/parsing				\
				Parsing/utils				\
				builtins/echo				\
				main						
				#builtins/pwd_cd			\

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
