# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 18:12:34 by dreis-ma          #+#    #+#              #
#    Updated: 2023/07/29 20:04:35 by dreis-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DEPS = libft/libft.a

SRC = src/main.c src/builtins/pwd.c src/builtins/exit.c \
src/builtins/change_dir.c src/builtins/echo.c src/builtins/exit_2.c \
src/signals.c src/builtins/env.c src/executor/executor.c src/lexer/lexer.c \
src/lexer/lexer_utils.c src/lexer/lexer_utils_2.c src/parser/parser.c \
src/parser/parser_utils.c src/builtins/utils_builtins.c src/builtins/unset.c \
src/error_free/error_builtins.c src/builtins/export.c src/executor/pipes.c \
src/executor/pipes_utils.c src/executor/executor_utils.c \
src/expander/expander.c src/expander/expander_utils.c \
src/redirections/redirections.c

OBJ = $(SRC:.c=.o)

NAME = minishell

LIBFT = libft/libft.a

all: deps $(NAME)

deps:
	$(MAKE) -C ./libft
$(NAME): $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean:
	$(MAKE) clean -C ./libft
	@rm -rf $(OBJ)

fclean: clean
	$(MAKE) $@ -C ./libft
	@rm -rf $(NAME)

re: fclean all
	$(MAKE) re -C ./libft
