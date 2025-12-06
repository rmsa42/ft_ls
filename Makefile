NAME = ft_ls

LIBFT = libft

SRC = ft_ls.c ft_ls_utils.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wextra -Wall -g
INCLUDES = $(LIBFT)
LIBFLAGS = -L$(LIBFT) -lft
DEBUG ?= 0
DEBUG_FLAG = -DDEBUG

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -sC $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(LIBFLAGS)
	
%.o: %.c
	$(CC) $(DEBUG_FLAG)=$(DEBUG) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -sC $(LIBFT) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -sC $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
