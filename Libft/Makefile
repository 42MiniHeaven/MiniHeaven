# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 15:14:44 by lwittwer          #+#    #+#              #
#    Updated: 2025/07/05 12:43:03 by lwittwer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c

NAME = libft.a
LIBC = ar rcs
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude
SRC_DIR = src/
OBJ_DIR = obj/
OBJ_SRCS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: ${NAME}

${NAME}: ${OBJ_SRCS}
	${LIBC} ${NAME} ${OBJ_SRCS}

$(OBJ_SRCS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	${CC} ${CFLAGS} -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -rf ${NAME}

re: fclean all
