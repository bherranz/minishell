NAME = minishell

SRCS = src/main.c

OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS:.c=.o}

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
REMOVE = rm -f


all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) > /dev/null

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

clean:
	$(REMOVE) $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(REMOVE) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

clear:
	@clear

.PHONY: all clean fclean re clear bonus