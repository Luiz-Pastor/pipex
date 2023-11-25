######################################################
CC := cc
CFLAGS := -Wall -Werror -Wextra
######################################################
NAME = pipex
SRC =	main.c
SRC_FOLDER = src
OBJ=$(SRC:%.c=%.o)
######################################################

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $(NAME)

%.o: $(SRC_FOLDER)/%.c
	$(CC) $(CFLAGS) -c $^

######################################################

run:
	./$(NAME) a b c d

valgrind:
	valgrind --leak-check=full ./$(NAME) a b c d

######################################################

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re