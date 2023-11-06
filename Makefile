# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dferjul <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 15:52:03 by dferjul           #+#    #+#              #
#    Updated: 2023/11/06 15:57:13 by dferjul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	$(shell find ./source -name '*.c')

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	echo "   \033[37;42;1m$(NAME) created\033[0m"

clean:
	rm -rf $(OBJS)
	echo "   \033[41;1mObject file deleted\033[0m"

fclean: clean
	rm -rf $(NAME)
	echo "   \033[41;1m$(NAME) deleted\033[0m"

re: fclean all

.SILENT:
.PHONY: all clean fclean re bonus
