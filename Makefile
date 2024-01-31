# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lribette <lribette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 10:03:29 by lribette          #+#    #+#              #
#    Updated: 2024/01/31 10:07:27 by lribette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =								\
				main				

INC_FILES = -I Pipex

SRC = $(addsuffix .c,$(SRCS))
OBJ = $(addsuffix .o,$(SRCS))

CC = cc
CCFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=20 -g

NAME = minishell

all: $(NAME)

$(NAME) : $(OBJ)
	$(MAKE) -C libft/ bonus
	$(CC) -o $@ $(OBJ) libft/libft.a

%.o: %.c
	$(CC) -c -o $@ $< $(CCFLAGS) $(INC_FILES)

clean :
	$(MAKE) -C libft/ clean
	rm -rf $(OBJ) $(BOBJ)

fclean : clean
	$(MAKE) -C libft/ fclean
	rm -rf $(NAME) $(BNAME)

re : fclean all

.PHONY : all bonus clean fclean re
