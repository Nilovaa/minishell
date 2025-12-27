
NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

READLINE_FLAGS = -lreadline -lncurses

SRCS = main.c cmd_line.c execution.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ../LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
