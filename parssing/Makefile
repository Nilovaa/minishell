NAME = minishell

SRC =	main.c \
		split_by_pipe.c \
		split_utils.c \
		ft_exit.c \
		ft_quote.c \
		tokenisation.c \

OBJ = $(SRC:.c=.o)

LIBFT = ./LIBFT/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./LIBFT
LDFLAGS = -lreadline $(LIBFT)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
