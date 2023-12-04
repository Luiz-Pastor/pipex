######################################################
CC := cc
CFLAGS := -Wall -Werror -Wextra -g3
######################################################
NAME = pipex
SRC =	main.c	\
		path.c	\
		arguments.c	\
		utils.c
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

test: all
	@cp pipex ../pipex_texter/
	@cd ../pipex_texter; ./pipex "assets/deepthought.txt" "wc -w" "cat" "outs/test-xx.txt";
	@cd ../pipex_texter; cat outs/test-xx.txt
	@cd ../pipex_texter; < assets/deepthought.txt wc -w | cat > outs/test-xx.txt; cat outs/test-xx.txt

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
