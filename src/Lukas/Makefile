# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/03 18:30:47 by lwittwer          #+#    #+#              #
#    Updated: 2026/02/03 19:14:55 by lwittwer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC := main.c \
		init.c \
		execute.c \
		env/env_init.c \
		env/env_utils.c \
		env/utils.c
		
NAME := MiniHeaven
CC := cc
CFLAGS := -Wall -Wextra -Werror -I Libft/include

OBJ := $(SRC:.c=.o)

LIBFT_DIR := ../../Libft
LIBFT := $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

