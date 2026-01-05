
NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

READLINE_FLAGS = -lreadline -lncurses

SRCS = main.c cmd_line.c execution.c pipe.c ../parsing/add_cmd.c ../parsing/ft_exit.c ../parsing/checker_pipe.c ../parsing/ft_quote.c ../parsing/list_pars.c ../parsing/pars_utils.c ../parsing/put_cmd.c ../parsing/split_by_pipe.c ../parsing/split_token.c ../parsing/split_utils.c ../parsing/struct_init.c ../parsing/tokenisation.c  
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ../../LIBFT
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
