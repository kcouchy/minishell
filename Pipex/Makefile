# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 10:04:34 by kcouchma          #+#    #+#              #
#    Updated: 2024/01/22 15:48:03 by kcouchma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =								\
				bonus_pipex			\
				bonus_cmds			\
				utils				\
				errors

BONUS_SRCS =						\

INC_FILES = -I libft

SRC = $(addsuffix .c,$(SRCS))
BSRC = $(addsuffix .c,$(BONUS_SRCS))
OBJ = $(addsuffix .o,$(SRCS))
BOBJ = $(addsuffix .o,$(BONUS_SRCS))

CC = cc
CCFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=20 -g

NAME = pipex
BNAME = bonus_pipex

all: $(NAME)

$(NAME) : $(OBJ)
	$(MAKE) -C libft/ bonus
	$(CC) -o $@ $(OBJ) libft/libft.a

bonus: all # redirected from the bonus command : $(BNAME)

$(BNAME) : $(BOBJ)
	$(MAKE) -C libft/ bonus
	$(CC) -o $@ $(BOBJ) libft/libft.a

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
