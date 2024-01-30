# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 10:04:34 by kcouchma          #+#    #+#              #
#    Updated: 2024/01/11 11:13:26 by kcouchma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =								\
				ft_isalpha			\
				ft_isdigit			\
				ft_isalnum			\
				ft_isascii			\
				ft_isprint			\
				ft_strlen			\
				ft_bzero			\
				ft_memcpy			\
				ft_memmove			\
				ft_tolower			\
				ft_memset			\
				ft_toupper			\
				ft_strlcpy			\
				ft_strlcat			\
				ft_strncmp			\
				ft_strnstr			\
				ft_strchr			\
				ft_strrchr			\
				ft_memchr			\
				ft_memcmp			\
				ft_atoi				\
				ft_atod				\
				ft_strdup			\
				ft_calloc			\
				ft_substr			\
				ft_strjoin			\
				ft_strtrim			\
				ft_split			\
				ft_itoa				\
				ft_strmapi			\
				ft_striteri			\
				ft_putchar_fd		\
				ft_putstr_fd		\
				ft_putendl_fd		\
				ft_putnbr_fd		\
				ft_putbase			\
				ft_printf			\
				get_next_line		\
				get_next_line_utils \

BONUS_SRCS =						\
				ft_lstnew			\
				ft_lstadd_front		\
				ft_lstsize			\
				ft_lstlast			\
				ft_lstadd_back		\
				ft_lstdelone		\
				ft_lstclear			\
				ft_lstiter			\
				ft_lstmap			\

INC_FILES = libft.h

SRC = $(addsuffix .c,$(SRCS))
BSRC = $(addsuffix .c,$(BONUS_SRCS))
OBJ = $(addsuffix .o,$(SRCS))
BOBJ = $(addsuffix .o,$(BONUS_SRCS))

CC = cc
CCFLAGS = -Wall -Wextra -Werror

NAME = libft.a

all: $(NAME)

$(NAME) : $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) -c $< -o $@ $(CCFLAGS)

bonus : $(OBJ) $(BOBJ)
	ar rcs $(NAME) $^

clean :
	rm -rf $(OBJ) $(BOBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re