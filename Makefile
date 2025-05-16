NAME = minishell
CC = cc

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_DIR = /usr/local/Cellar/readline/8.2.13

CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_DIR) -I$(READLINE_DIR)/include
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(READLINE_DIR)/lib -lreadline -lncurses

SRC_PATH = srcs/
OBJ_PATH = objs/

SRC =	main.c \
		expander.c \
		clean_utils.c \
		tokenizer/tokenizer.c \
		tokenizer/token_utils.c \
		tokenizer/token_operator.c \
		tokenizer/token_word.c \
		tokenizer/token_quotes.c \
		parser/parser.c \
		execution/execution.c \
		execution/path_utils.c \
		execution/processes.c \
		built_ins/built_in.c \
		built_ins/ft_echo.c \
		built_ins/ft_cd.c \
		built_ins/ft_pwd.c \
		built_ins/ft_export.c \
		built_ins/ft_env.c \
		built_ins/ft_unset.c \

OBJ = $(SRC:.c=.o)

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRCS))

all: $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_PATH)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
