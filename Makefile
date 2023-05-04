# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 18:12:34 by dreis-ma          #+#    #+#              #
#    Updated: 2023/05/01 18:12:37 by dreis-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DEPS = libft/libft.a

SRC = src/main.c src/prompt_split.c src/builtins/pwd.c \
src/builtins/change_dir.c src/builtins/echo.c src/builtins/exit.c

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
