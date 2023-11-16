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
SRCS =	$(shell find ./sources -name '*.c')

OBJ_DIR = Objects

OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

LIB = libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft --no-print-directory
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -lreadline -o $(NAME)
	echo "   \033[37;42;1m$(NAME) created\033[0m"

clean:
	make clean -C libft --no-print-directory
	rm -rf $(OBJS) $(OBJ_DIR)
	echo "   \033[41;1mObject file deleted\033[0m"

fclean: clean
	make fclean -C libft --no-print-directory
	rm -rf $(NAME)
	echo "   \033[41;1m$(NAME) deleted\033[0m"

re: fclean all

.SILENT:
.PHONY: all clean fclean re
