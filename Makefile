# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 11:01:54 by mabenet           #+#    #+#              #
#    Updated: 2024/10/15 15:35:24 by mabenet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

SRC = main.c \
	treat_input.c \
	format_check.c \

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) -lreadline -lhistory -lm
	echo "Ready to minishell"

clean:
	rm -rf $(SRC:.c=.o)
	echo "OBJ deleted"

fclean: clean
	rm -rf $(NAME)
	echo "$(NAME) deleted"

re: fclean all

.PHONY: all, clean, fclean, re, bonus

.SILENT: