# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldeirdre <ldeirdre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/31 21:54:04 by ldeirdre          #+#    #+#              #
#    Updated: 2020/11/13 18:39:46 by ldeirdre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR  := ./srcs
INC_DIR  := ./inc
OBJ_DIR  := ./obj

SRC		:= 	ft_printf.c init.c parser.c \
			type_char.c dispatcher.c \
			type_string.c libft_func2.c\
			type_pointer.c type_int.c \
			type_float.c type_base.c\
			float_util.c write_float.c libft_func.c \
			
OBJ		:= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror

PRINTF_NAME	:= libftprintf.a

NAME	:= $(PRINTF_NAME)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(INC_DIR)/printf.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rc $(PRINTF_NAME) $(OBJ)
	ranlib $(PRINTF_NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(PRINTF_NAME)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re relibs test
