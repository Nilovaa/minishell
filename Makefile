NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

READLINE_FLAGS = -lreadline -lncurses

SRCS = src/execution/main.c \
		src/execution/cmd_line.c \
		src/execution/cmd_utils.c \
		src/execution/main_loop.c \
		src/execution/execution.c \
		src/execution/execution_utils.c \
		src/execution/execution_utils1.c \
		src/execution/pipe.c \
		src/execution/pipe_utils.c \
		src/execution/pipe_utils2.c \
		src/execution/pipeline.c \
		src/execution/pipeline_utils.c \
		src/execution/pipeline_utils1.c \
		src/execution/pipeline_utils2.c \
		src/execution/redirection.c \
		src/execution/redirection_utils.c \
		src/execution/redirection_utils1.c \
		src/execution/redirection_utils2.c \
		src/execution/signal.c \
		src/execution/signal_utils.c \
		src/execution/signal_utils1.c \
		src/parsing/add_cmd.c \
		src/parsing/ft_exit.c \
		src/parsing/checker_pipe.c \
		src/parsing/ft_quote.c \
		src/parsing/list_pars.c \
		src/parsing/list_pars_utils.c \
		src/parsing/pars_utils.c \
		src/parsing/token_utils.c \
		src/parsing/put_cmd.c \
		src/parsing/split_by_pipe.c \
		src/parsing/split_token.c \
		src/parsing/split_utils.c \
		src/parsing/struct_init.c \
		src/parsing/tokenisation.c \
		src/parsing/ft_list_str.c \
		src/parsing/ft_expander.c \
		src/parsing/expander_utils.c \
		src/parsing/expander_utils1.c \
		src/builtins/check_builtins.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/exit.c \
		src/builtins/export.c \
		src/builtins/export_utils.c \
		src/builtins/pwd.c \
		src/builtins/unset.c \
		src/builtins/unset_utils.c \
		src/builtins/cd.c \
		src/builtins/cd_utils.c \

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
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
