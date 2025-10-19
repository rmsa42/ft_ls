NAME = ft_ls

LIBFT = libft

SRC = ft_ls.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wextra -Wall
INCLUDES = $(LIBFT)
LIBFLAGS = -L$(LIBFT) -lft

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -sC $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(LIBFLAGS)
	
%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -sC $(LIBFT) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -sC $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
