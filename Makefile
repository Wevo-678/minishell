# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 11:01:54 by mabenet           #+#    #+#              #
#    Updated: 2024/10/16 15:06:30 by mabenet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

SRC = cd_pwd.c \
	cheking_args.c \
	array_utils.c \
	format_check.c \
	main.c \
	split_them_all.c \
	str_utils.c \
	struct_init.c \
	treat_input.c \
	split_node.c \

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