# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/03 18:30:47 by lwittwer          #+#    #+#              #
#    Updated: 2026/02/14 15:18:34 by lwittwer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC := src/main.c \
		src/AJ/lexer.c \
		src/AJ/parser.c \
		src/Lukas/init.c \
		src/Lukas/dispatcher.c \
		src/Lukas/exec_builtin.c \
		src/Lukas/free.c \
		src/Lukas/forking.c \
		src/Lukas/redirections.c \
		src/Lukas/fds.c \
		src/Lukas/heredoc.c \
		src/Lukas/env/env_init.c \
		src/Lukas/env/env_utils.c \
		src/Lukas/env/env_set.c \
		src/Lukas/env/env_unset.c \
		src/Lukas/env/utils.c \
		src/Lukas/builtins/builtins.c \
		src/Lukas/builtins/builtin_cd.c \
		src/Lukas/builtins/builtin_echo.c \
		src/Lukas/builtins/builtin_env.c \
		src/Lukas/builtins/builtin_exit.c \
		src/Lukas/builtins/builtin_export.c \
		src/Lukas/builtins/builtin_pwd.c \
		src/Lukas/builtins/builtin_unset.c \
		src/Lukas/external/resolve.c
		
NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror -I Libft/include
LDLIBS := -lreadline

OBJ := $(SRC:.c=.o)

LIBFT_DIR := Libft
LIBFT := $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDLIBS) -o $(NAME)

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

