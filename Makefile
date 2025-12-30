NAME = minishell

SRC =	src/parsing/main.c \
		src/parsing/split_by_pipe.c \
		src/parsing/split_utils.c \
		src/parsing/ft_exit.c \
		src/parsing/ft_quote.c \
		src/parsing/tokenisation.c \
		src/parsing/struct_init.c \
		src/parsing/checker_pipe.c \
		src/parsing/list_pars.c \
		src/parsing/split_token.c \
		src/parsing/put_cmd.c \
		src/parsing/pars_utils.c \
		src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/exit.c \
		src/builtins/export.c \
		src/builtins/pwd.c \
		src/builtins/unset.c \
		src/execution/execution.c \
		src/execution/cmd_line.c \
		src/execution/main.c
		
OBJ = $(SRC:.c=.o)

LIBFT = LIBFT/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I./LIBFT

LDFLAGS = -lreadline $(LIBFT)

all: $(NAME)

$(NAME): $(OBJ)
		make -C LIBFT
		$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		make clean -C LIBFT
		rm -f $(OBJ)

fclean: clean
		make fclean -C LIBFT
		rm -f $(NAME)

re: fclean all

