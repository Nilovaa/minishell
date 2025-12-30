# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 14:24:36 by nyrakoto          #+#    #+#              #
#    Updated: 2025/06/26 16:27:03 by nyrakoto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

COMPILE = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalpha.c ft_isalnum.c \
       ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
       ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strdup.c \
       ft_strlen.c ft_strchr.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
       ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
       ft_tolower.c ft_toupper.c ft_split.c ft_strmapi.c ft_striteri.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_strjoin3.c

BONUS = $(SRCS) ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c \
		ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJS = ${SRCS:.c=.o}

LIBC = ar rcs

OBJS_BONUS = ${BONUS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBC) $@ $^

%.o: %.c
	$(COMPILE) $(CFLAGS) -c $< -o $@

bonus:$(OBJS_BONUS)
	$(LIBC) $(NAME) $(OBJS_BONUS)


clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
