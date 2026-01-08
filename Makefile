NAME = MiniHeaven

SRC = src/main.c

OBJ = $(SRC:.c=.o)

CC = CC
CFLAGS = -Wall -Werror -Wextra -Iinclude

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

