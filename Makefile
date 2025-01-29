NAME = cub3D

SOURCES = main.c parse_map.c parse_map_utils.c parse_color.c parse_element.c file_validation.c validate_map.c  calculate.c  raycast.c movement.c calculate_utils.c draw_functions.c draw_utils.c hooks.c check_walls.c

OBJECTS = $(SOURCES:.c=.o)

BOBJECTS = $(BSOURCES:.c=.o) 

LIBFT = ./libft/libft.a

MLX42 = ./MLX42/build/libmlx42.a

CC = cc

CFLAGS += -g -I./MLX42/include

LDFLAGS = -L./MLX42/build -lmlx42 -ldl -lglfw -lm -lpthread

RM = rm -f

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(MLX42):
	cmake -S ./MLX42 -B ./MLX42/build
	$(MAKE) -C ./MLX42/build

$(NAME): $(OBJECTS) $(LIBFT) $(MLX42)
	$(CC) $(OBJECTS) $(LIBFT) $(LDFLAGS) -o $(NAME)

bonus: all 

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJECTS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
