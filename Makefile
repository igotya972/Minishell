SHELL := /bin/bash

SRCS = $(shell find ./sources -name '*.c')

OBJ_DIR = Objects

OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

LIB = libft/libft.a

TOTAL_FILES = $(words $(SRCS))

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@tput civis
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@count=$$(find $(OBJ_DIR) -name '*.o' | wc -l); \
	i=1; \
	while [ $$i -le $$count ]; do \
		echo -n "▰ "; \
		i=$$((i + 1)); \
	done; \
	while [ $$i -le $(TOTAL_FILES) ]; do \
		echo -n "══"; \
		i=$$((i + 1)); \
	done; \
	echo -en "  $$((($$count * 100) / $(TOTAL_FILES)))% Compiling $$(basename $<)...\r"

$(NAME): $(OBJS)
	@make -C libft --no-print-directory
	@printf "\033[2K\r"
	@echo -en "   \033[37;42;1mlibft created\033[0m\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -lreadline -o $(NAME)
	@echo -en "   \033[37;42;1m$(NAME) created\033[0m\n"
	@tput cnorm

clean:
	@make clean -C libft --no-print-directory
	@rm -rf $(OBJS) $(OBJ_DIR)
	@echo -e "   \033[41;1mObject file deleted\033[0m"

fclean: clean
	@make fclean -C libft --no-print-directory
	@rm -rf $(NAME)
	@echo -e "   \033[41;1m$(NAME) deleted\033[0m"

re: fclean all

.SILENT:
.PHONY: all clean fclean re
