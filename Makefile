# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dferjul <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 15:52:03 by dferjul           #+#    #+#              #
#    Updated: 2023/11/14 13:58:00 by dferjul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR = sources

SRCS =	$(shell find $(SRC_DIR) -name '*.c')

OBJ_DIR = Objects

OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
	echo "   \033[37;42;1m$(NAME) created\033[0m"

clean:
	rm -rf $(OBJS) $(OBJ_DIR)
	echo "   \033[41;1mObject file deleted\033[0m"

fclean: clean
	rm -rf $(NAME)
	echo "   \033[41;1m$(NAME) deleted\033[0m"

re: fclean all

.SILENT:
.PHONY: all clean fclean re
