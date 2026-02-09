# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/03 18:30:47 by lwittwer          #+#    #+#              #
#    Updated: 2026/02/09 22:57:39 by lwittwer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC := main.c \
		init.c \
		dispatcher.c \
		exec_builtin.c \
		free.c \
		forking.c \
		redirections.c \
		fds.c \
		env/env_init.c \
		env/env_utils.c \
		env/env_set.c \
		env/env_unset.c \
		env/utils.c \
		builtins/builtins.c \
		builtins/builtin_cd.c \
		builtins/builtin_echo.c \
		builtins/builtin_env.c \
		builtins/builtin_exit.c \
		builtins/builtin_export.c \
		builtins/builtin_pwd.c \
		builtins/builtin_unset.c \
		external/resolve.c
		
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

