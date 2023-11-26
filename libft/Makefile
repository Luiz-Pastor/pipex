##############################################################################
CC := cc
FLAGS := -Wall -Werror -Wextra -O3
##############################################################################
LIBFT_NAME=libft.a
##############################################################################
SRC_FOLDER=src
##############################################################################

# Obligatory files
LIBFT_FILES=	ft_memset.c		\
			ft_bzero.c		\
			ft_memcpy.c		\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_strlen.c		\
			ft_strchr.c		\
			ft_strrchr.c	\
			ft_strncmp.c	\
			ft_atoi.c		\
			ft_isalpha.c	\
			ft_isdigit.c	\
			ft_isalnum.c	\
			ft_isascii.c	\
			ft_isprint.c	\
			ft_toupper.c	\
			ft_tolower.c	\
			ft_calloc.c		\
			ft_strdup.c		\
			ft_strlcat.c	\
			ft_memmove.c	\
			ft_strnstr.c	\
			ft_strlcpy.c	\
			ft_substr.c		\
			ft_strjoin.c	\
			ft_strtrim.c	\
			ft_split.c		\
			ft_itoa.c		\
			ft_strmapi.c	\
			ft_striteri.c	\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c
LIBFT_OBJ=$(LIBFT_FILES:%.c=%.o)

# Optional files (bonus part)
LIBFT_BONUS_FILES=	ft_lstnew.c		\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_back.c	\
				ft_lstdelone.c		\
				ft_lstclear.c		\
				ft_lstiter.c		\
				ft_lstmap.c
LIBFT_BONUS_OBJ=$(LIBFT_BONUS_FILES:%.c=%.o)

# Get_next_line files
LIBFT_GNL_FILES= 	get_next_line.c			\
					get_next_line_utils.c
LIBFT_GNL_OBJ=$(LIBFT_GNL_FILES:%.c=%.o)

# File that I created
LIBFT_PERSONAL_FILES=	ft_strcmp.c
LIBFT_PERSONAL_OBJ=$(LIBFT_PERSONAL_FILES:%.c=%.o)

##############################################################################

all: $(LIBFT_NAME)

$(LIBFT_NAME): $(LIBFT_OBJ) $(LIBFT_BONUS_OBJ) $(LIBFT_GNL_OBJ) $(LIBFT_PERSONAL_OBJ)
	@ar crs $(LIBFT_NAME) $^

# It compiles all the .c files to .o if it is necessary
%.o: $(SRC_FOLDER)/%.c
	$(CC) $(FLAGS) -c $<

##############################################################################

# "nm", "norm" and "norminette" check if the c and h files are ok according to the standard
nm: norminette
norm: norminette
norminette:
	@norminette src/ libft.h

# "clean" deletes all the .o files
clean:
	@rm -f $(LIBFT_OBJ) $(LIBFT_BONUS_OBJ) $(LIBFT_GNL_OBJ) $(LIBFT_PERSONAL_OBJ)

# "fclean" deletes all the .o files and the library generated
fclean: clean
	@rm -f $(LIBFT_NAME)

# "fclear" deletes all the .o files, the lybrary generated and make a new one
re: fclean $(LIBFT_NAME)

# ".PHONY" is added to prevent it from detecting files named "all", "clean", "fclean" or "re"
.PHONY: all clean fclean re

##############################################################################

env:
	@rm -rf .gitignore README.md .git tests/
