# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miparis <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/20 11:55:30 by miparis           #+#    #+#              #
#    Updated: 2024/08/20 11:55:32 by miparis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/main.c

# Define Colors
GREEN  := \033[1;32m  # Bold Green
YELLOW := \033[0;33m  # Non-bold Yellow
RED    := \033[0;31m  # Regular Red
BLUE   := \033[1;34m  # Bold Blue
PURPLE := \033[1;35m  # Bold Purple
BOLD   := \033[1m     # Bold Text
NC     := \033[0m     # No Color (Resets color and style)

OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS:.c=.o}

.SILENT: $(OBJS)

LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = inc/printf 
PRINTF = $(PRINTF_DIR)/libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
REMOVE = rm -f

all: $(LIBFT) $(PRINTF) $(MLX_LIB) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) > /dev/null
	@echo "$(BOLD)$(YELLOW)📚Libft compiled... $(NC)"

$(PRINTF):
	@make -C $(PRINTF_DIR) > /dev/null
	@echo "$(BOLD)$(YELLOW)🖨️ Printf compiled... $(NC)"

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf -o $(NAME)
	@echo "$(BOLD)$(BLUE)🐚Minishell is now operative$(NC)"


clean:
	@$(REMOVE) $(OBJS)
	@make -C $(LIBFT_DIR) clean > /dev/null
	@make -C $(PRINTF_DIR) clean > /dev/null

fclean: clean
	@$(REMOVE) $(NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@make -C $(PRINTF_DIR) fclean > /dev/null
	@echo "$(BOLD)$(GREEN)🧹Everything cleaned up!$(NC)"

re: fclean all

clear:
	@clear

.PHONY: all clean fclean re clear bonus
