# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/20 11:55:30 by miparis           #+#    #+#              #
#    Updated: 2025/02/10 15:31:51 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRCS =  src/main.c \
		src/free_utils.c \
		src/parser/parser.c \
		src/parser/parser_utils.c \
		src/parser/parser_utils2.c \
		src/parser/parser_cmd.c \
		src/parser/parser_cmd2.c \
		src/parser/parser_fds.c \
		src/parser/parser_fds2.c \
		src/utils.c \
		src/signals/signals.c \
		src/signals/here_doc.c \
		src/expansor/expansor.c \
		src/expansor/expansor_utils.c \
		src/executor/executor.c \
		src/executor/fds_utils.c \
		src/executor/here_doc.c \
		src/executor/single_process.c \
		src/executor/multiple_processes.c \
		src/executor/paths_args.c \
		src/executor/process_utils.c \
		src/executor/utils.c \
		src/built-in/builtins.c \
		src/built-in/ft_echo.c \
		src/built-in/ft_cd.c \
		src/built-in/ft_cd2.c \
		src/built-in/ft_pwd.c \
		src/built-in/ft_export.c \
		src/built-in/ft_export2.c \
		src/built-in/ft_env.c \
		src/built-in/ft_unset.c \
		src/built-in/ft_exit.c \
		src/config_envp.c \
		src/shell_level.c \

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

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
REMOVE = rm -f

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) > /dev/null
	@echo "$(BOLD)$(YELLOW)📚Libft compiled... $(NC)"

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lft -lreadline -o $(NAME)
	@echo "$(BOLD)$(BLUE)🐚Minishell is now operative$(NC)"


clean:
	@$(REMOVE) $(OBJS)
	@make -C $(LIBFT_DIR) clean > /dev/null

fclean: clean
	@$(REMOVE) $(NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@echo "$(BOLD)$(GREEN)🧹Everything cleaned up!$(NC)"

re: fclean all

clear:
	@clear

.PHONY: all clean fclean re clear bonus
