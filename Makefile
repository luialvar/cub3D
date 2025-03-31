FLAGS = -Wall -Wextra -Werror -g

NAME = cub3D

PARSER_FILES = srcs_parser/get_next_line.c srcs_parser/error_checker.c srcs_parser/libft1.c srcs_parser/libft2.c

EXEC_FILES = 

OBJ = $(PARSER_FILES:%.c=%.o)

EXEC_OBJ = $(EXEC_FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(EXEC_OBJ)
	cc $(FLAGS) $(OBJ) $(EXEC_OBJ) -o $(NAME)

%.o: %.c
	clang -c $(FLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(EXEC_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

