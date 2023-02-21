NAME = pipex

SRC = parsing.c pipex.c paths.c free_stuff.c family.c parsing_utils.c

OBJ = $(SRC:%.c=%.o)

FLAGS= -Wall -Wextra -Werror -fsanitize=address

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@cc $(SRC) $(LIBFT) $(FLAGS) -o $(NAME)

$(LIBFT):
	@make -C ./libft
	@make bonus -C ./libft

clean:
	@/bin/rm -f $(OBJ)
	@make clean -C ./libft
	
fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C ./libft