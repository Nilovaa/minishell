# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 19:24:08 by andriamr          #+#    #+#              #
#    Updated: 2025/04/08 16:38:55 by andriamr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_strlen.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memmove.c \
		ft_memcpy.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \

CC = gcc

FLAG = -Wall -Werror -Wextra

NAME = libft.a

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(FLAG) -o $@ -c $<

$(NAME) : $(OBJ)
	-ar rsc -o $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
