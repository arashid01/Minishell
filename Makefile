NAME = minishell
CC = cc

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_DIR = /usr/local/Cellar/readline/8.2.13

CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_DIR) -I$(READLINE_DIR)/include
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(READLINE_DIR)/lib -lreadline

SRCS =  srcs/main.c srcs/tokenizing.c
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)


$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) || exit 1

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re