# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dferjul <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 13:40:08 by dferjul           #+#    #+#              #
#    Updated: 2023/11/14 11:12:05 by dferjul          ###   ########.fr        #
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

#--Règle pour compiler les fichiers .c en fichiers .o--#
 $(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

#rules

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

bonus : $(OBJS_BONUS)
		ar -rcs $(NAME) $(OBJS_BONUS)

clean :
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all, libft.a, clean, fclean, re, bonus
