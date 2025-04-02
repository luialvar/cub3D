FLAGS = -Wall -Wextra -Werror -g

NAME = cub3D

PARSER_FILES = srcs_parser/help_functions/get_next_line.c \
				srcs_parser/main.c \
				srcs_parser/pre_creating_structure/check_program_params.c \
				srcs_parser/help_functions/auxiliary1.c \
				srcs_parser/help_functions/auxiliary2.c \
				srcs_parser/help_functions/auxiliary3.c \
				srcs_parser/pre_creating_structure/storing_lines_type.c \
				srcs_parser/pre_creating_structure/line_type_decider.c \
				srcs_parser/pre_creating_structure/check_valid_map_info.c \
				srcs_parser/help_functions/ft_split.c

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

