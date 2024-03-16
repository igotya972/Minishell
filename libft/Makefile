# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afont <afont@student.42nice.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 13:40:08 by dferjul           #+#    #+#              #
#    Updated: 2024/02/09 12:07:42 by afont            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	$(shell find $(SRC_DIR) -name '*.c')

SRCS_BONUS = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstclear.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstmap.c \

OBJ_DIR = obj_o

OBJS	= 	$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

RM		=	rm -rf

NAME	=	libft.a

TOTAL_FILES = $(words $(SRCS))

$(OBJ_DIR)/%.o: %.c
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

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

bonus : $(OBJS_BONUS)
	@ar -rcs $(NAME) $(OBJS_BONUS)

clean :
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@rm -rf obj_o

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.SILENT:
.PHONY : all, libft.a, clean, fclean, re, bonus
