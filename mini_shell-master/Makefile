# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 17:11:58 by sgil-moy          #+#    #+#              #
#    Updated: 2024/01/31 18:30:17 by egomez-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra 

NAME = minishell

SRCS =	main.c						\
		envp.c						\
		parse/parse.c				\
		parse/infile_finder.c		\
		parse/infile_finder_aux.c	\
		parse/cmd_finder.c			\
		parse/outfile_finder.c		\
		parse/here_doc/here_doc.c	\
		parse/here_doc/gnl.c		\
		parse/here_doc/gnl_utils.c	\
		parse/parse_split.c 		\
		parse/parse_utils.c 		\
		parse/quotes.c 				\
		parse/quotes_aux.c			\
		parse/variables.c 			\
		pipex/childs.c				\
		pipex/childs_aux.c			\
		pipex/forks.c				\
		pipex/pipex.c				\
		pipex/rutes.c				\
		pipex/one_child.c			\
		built-ins/cd.c				\
		built-ins/pwd.c				\
		built-ins/builtins.c		\
		built-ins/envp.c			\
		built-ins/export.c			\
		built-ins/unset.c			\
		built-ins/echo.c			\
		built-ins/exit.c			\
		signals/signals.c			\

		
OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(OBJS) -o $(NAME) -Llibft/ -lft -lreadline

libft/libft.a:
	make -sC libft/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean $(NAME)

.PHONY: clean fclean re

del:
	@./a.out

clear:
	@clear

run: clear $(NAME)
	@./$(NAME)