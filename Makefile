FLAGS = -Wall -Wextra -Werror -g

NAME = cub3D

PARSER_FILES = srcs_parser/get_next_line.c \
				srcs_parser/main.c \
				srcs_parser/check_program_params.c \
				srcs_parser/auxiliary1.c \
				srcs_parser/auxiliary2.c \
				srcs_parser/storing_lines_type.c \
				srcs_parser/line_type_decider.c \
				srcs_parser/ft_split.c

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

