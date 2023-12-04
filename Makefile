######################################################
CC := cc
CFLAGS := -Wall -Werror -Wextra
######################################################
NAME = pipex
SRC =	main.c	\
		path.c	\
		arguments.c
SRC_FOLDER = src
OBJ=$(SRC:%.c=%.o)
######################################################

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) $^ -o $(NAME)

libft/libft.a:
	@make -C libft/

%.o: $(SRC_FOLDER)/%.c
	$(CC) $(CFLAGS) -c $^

######################################################

test:
	@norminette > test.txt

run: all
	@rm -rf result.txt
	@./$(NAME) test.txt "grep -v OK" "grep EMPTY_LINE_FUNCTION" result.txt

awk: all
	@echo "==============================\n\n"
	@./$(NAME) test.txt "cat" "awk '\$$1 == "Error:" {print \$$2}' Hola \"Hola\"" result.txt

valgrind: all
	@rm -rf result.txt
	@valgrind --leak-check=full ./$(NAME) test.txt "grep -v OK" "grep CONSECUTIVE_NEWLINES" result.txt

######################################################

clean:
	@rm -rf $(OBJ)
	@make -C libft/ clean
	@rm -rf test.txt
	@rm -rf result.txt

fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: clean fclean re all
