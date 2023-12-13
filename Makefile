######################################################
CC := cc
CFLAGS := -Wall -Werror -Wextra -g3
######################################################
NAME = pipex

# Mandatory part
SRC =	main.c		\
		path.c		\
		arguments.c	\
		utils.c		\
		executes.c
SRC_FOLDER = src
OBJ=$(SRC:%.c=%.o)

# Bonus part
BONUS_SRC =	main_bonus.c		\
			path_bonus.c		\
			arguments_bonus.c	\
			utils_bonus.c		\
			here_doc_bonus.c
BONUS_FOLDER = srcbonus
BONUS_OBJ=$(BONUS_SRC:%.c=%.o)
######################################################

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) $^ -o $(NAME)

bonus: $(BONUS_OBJ) libft/libft.a
	$(CC) $^ -o $(NAME)

libft/libft.a:
	@make -C libft/

%.o: $(SRC_FOLDER)/%.c
	$(CC) $(CFLAGS) -c $^

%.o: $(BONUS_FOLDER)/%.c
	$(CC) $(CFLAGS) -c $^

######################################################

clean:
	@rm -rf $(OBJ) $(BONUS_OBJ)
	@make -C libft/ clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: clean fclean re all
