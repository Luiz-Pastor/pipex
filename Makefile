######################################################
CC := cc
CFLAGS := -Wall -Werror -Wextra
######################################################
NAME = pipex
SRC =	main.c	\
		path.c
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

run: all
	@./$(NAME) test.txt "grep -v OK" "grep CONSECUTIVE_NEWLINES" errors.log

valgrind:
	@valgrind --leak-check=full ./$(NAME) a b c d

######################################################

clean:
	@rm -rf $(OBJ)
	@make -C libft/ clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: clean fclean re all