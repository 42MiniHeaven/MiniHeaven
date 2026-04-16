# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/03 18:30:47 by lwittwer          #+#    #+#              #
#    Updated: 2026/04/16 22:15:19 by lwittwer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC := src/main.c \
		src/check_args.c \
		src/error.c \
		src/free.c \
		src/free_environment.c \
		src/free_call.c \
		src/loop.c \
		src/loop_utils.c \
		src/shell_init.c \
		src/AJ/0_quotes.c \
		src/AJ/0_quotes_heredoc.c \
		src/AJ/0_signals.c \
		src/AJ/0_signals_utils.c \
		src/AJ/1_lexer.c \
		src/AJ/1_lexer_utils.c \
		src/AJ/2_parser.c \
		src/AJ/2_parser_utils.c \
		src/AJ/2_parser_utils2.c \
		src/AJ/2_parser_exit.c \
		src/AJ/3_expander.c \
		src/AJ/3_expander_mask.c \
		src/AJ/3_expander_check.c \
		src/AJ/3_expander_split.c \
		src/AJ/3_expander_split2.c \
		src/AJ/3_expander_utils.c \
		src/AJ/3_expander_redir.c \
		src/AJ/3_expander_core.c \
		src/AJ/3_expander_core_redir.c \
		src/AJ/4_expander_heredoc.c \
		src/AJ/4_heredoc.c \
		src/Lukas/child.c \
		src/Lukas/child_utils.c \
		src/Lukas/execute.c \
		src/Lukas/exec_single.c \
		src/Lukas/exec_external.c \
		src/Lukas/exec_builtin.c \
		src/Lukas/exec_pipe.c \
		src/Lukas/fds.c \
		src/Lukas/redirections.c \
		src/Lukas/heredoc.c \
		src/Lukas/heredoc_tmpfile.c \
		src/Lukas/heredoc_utils.c \
		src/Lukas/wfork.c \
		src/Lukas/wpipe.c \
		src/Lukas/wopen.c \
		src/Lukas/wclose.c \
		src/Lukas/wdup2.c \
		src/Lukas/exit_child.c \
		src/Lukas/builtins/builtin_cd.c \
		src/Lukas/builtins/builtin_echo.c \
		src/Lukas/builtins/builtin_export.c \
		src/Lukas/builtins/builtin_exit.c \
		src/Lukas/builtins/builtin_env.c \
		src/Lukas/builtins/builtin_unset.c \
		src/Lukas/builtins/builtin_pwd.c \
		src/Lukas/builtins/builtins.c \
		src/Lukas/env/create_node.c \
		src/Lukas/env/env_init.c \
		src/Lukas/env/env_add.c \
		src/Lukas/env/env_remove.c \
		src/Lukas/env/env_set.c \
		src/Lukas/env/env_find.c \
		src/Lukas/env/env_update.c \
		src/Lukas/env/empty_env.c \
		src/Lukas/env/env_utils.c \
		src/Lukas/env/env_get.c \
		src/Lukas/external/resolve.c \
		src/Lukas/external/env_arr.c \
		readFile.c
		

NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror -I Libft/include -I include -g
LDLIBS := -lreadline

OBJ := $(SRC:.c=.o)

LIBFT_DIR := Libft
LIBFT := $(LIBFT_DIR)/libft.a

.SILENT: all $(NAME)

all: banner $(LIBFT) $(NAME)

debug:
	$(MAKE) CFLAGS="$(CFLAGS) -g" re

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDLIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug $(LIBFT)

banner:
	@echo '  __  __ _       _ _   _'
	@echo ' |  \/  (_)_ __ (_) | | | ___  __ ___   _____ _ __'
	@echo ' | |\/| | | '\''_ \| | |_| |/ _ \/ _` \ \ / / _ \ '\''_ \ '
	@echo ' | |  | | | | | | |  _  |  __/ (_| |\ V /  __/ | | |'
	@echo ' |_|  |_|_|_| |_|_|_| |_|\___|\__,_| \_/ \___|_| |_|'
	@echo ' | |__  _   _                                       '
	@echo ' | '\''_ \| | | |                                      '
	@echo ' | |_) | |_| |                                      '
	@echo ' |_.__/ \__, |                                      '
	@echo '        |___/      _       _         ___            '
	@echo '   __ _ ___(_) ___| |_ __ (_) ___   ( _ )           '
	@echo '  / _` |_  / |/ _ \ | '\''_ \| |/ __|  / _ \/\         '
	@echo ' | (_| |/ /| |  __/ | | | | | (__  | (_>  <         '
	@echo '  \__,_/___|_|\___|_|_| |_|_|\___|  \___/\/         '
	@echo ' | |_      _(_) |_| |___      _____ _ __            '
	@echo ' | \ \ /\ / / | __| __\ \ /\ / / _ \ '\''__|           '
	@echo ' | |\ V  V /| | |_| |_ \ V  V /  __/ |              '
	@echo ' |_| \_/\_/ |_|\__|\__| \_/\_/ \___|_|              '
	@echo ''
