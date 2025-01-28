#include "cub3d.h"
void	error(char *error_message)
{
	printf("%s\n", error_message);
	exit(EXIT_FAILURE);
}

void	print_game_state(t_game *game)
{
	int	i;

    printf("Map Dimensions: %d (width) x %d (height)\n", game->map.width, game->map.height);
    printf("Textures:\n");
    printf("  NO: %s\n", game->map.no_text);
    printf("  SO: %s\n", game->map.so_text);
    printf("  WE: %s\n", game->map.we_text);
    printf("  EA: %s\n", game->map.ea_text);
    printf("Colors:\n");
    printf("  Floor: %d , %d , %d\n", game->map.floor_color[0], game->map.floor_color[1], game->map.floor_color[2]);
    printf("  Ceiling: %d , %d , %d\n", game->map.ceiling_color[0], game->map.ceiling_color[1], game->map.ceiling_color[2]);
    printf("Player:\n");
    printf("  Position: (x,y) (%d,%d)\n", game->player.x, game->player.y);
    printf("  Orientation: %c\n", game->player.player_pos);
    printf("Map:\n");
	i = 0;
    while (i < game->map.height)
	{
		printf("%s\n", game->map.points[i]);
		i++;
    }
}

int	check_cub_file(const char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len <= 4)
		return (0);
	if (ft_strncmp(file + len - 4, ".cub", 4) == 0)
		return (1);
	return (0);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.points)
	{
		while (game->map.points[i])
		{
			free(game->map.points[i]);
			i++;
		}
		free(game->map.points);
	}
	if (game->map.no_text)
		free(game->map.no_text);
	if (game->map.so_text)
		free(game->map.so_text);
	if (game->map.ea_text)
		free(game->map.ea_text);
	if (game->map.we_text)
		free(game->map.we_text);
	if (game->map.floor_color)
		free(game->map.floor_color);
	if (game->map.ceiling_color)
		free(game->map.ceiling_color);
}

int	init_values(t_game *game)
{
	game->mlx_ptr = 0;
	game->win_ptr = 0;

	game->map.points = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.no_text = NULL;
	game->map.so_text = NULL;
	game->map.we_text = NULL;
	game->map.ea_text = NULL;
	game->map.floor_color = malloc(3 * sizeof(int));
	if (!game->map.floor_color)
		return (0);
	game->map.ceiling_color = malloc(3 * sizeof(int));
	if (!game->map.ceiling_color)
	{
		free(game->map.floor_color);
		return (0);
	}
	game->map.floor_color[0] = -1;
	game->map.ceiling_color[0] = -1;

	game->player.x = -1;
	game->player.y = -1;
	game->player.player_pos = '\0';
	return (1);
}




int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
void paint_block(t_game *game, int x, int y, int flag)
{
	int z;
	int a;
	uint32_t	color_block;
	uint32_t	color_empty;

	color_block = ft_pixel( 200, 100, 0, 255);
	color_empty = ft_pixel( 255, 255, 255, 255);
	z = 0;
	a = 0;
	x *= BLOCK_SIZE / 6;
	y *= BLOCK_SIZE / 6;
	//printf ("%d", flag);
	while (z < BLOCK_SIZE/ 6)
	{
		while (a < BLOCK_SIZE/ 6)
		{
			if (flag == 1)
				mlx_put_pixel(game->image, x, y, color_block);
			else
				mlx_put_pixel(game->image, x, y, color_empty);
			a++;
			x++;
		}
		a = 0;
		x -= BLOCK_SIZE/ 6;
		//mlx_put_pixel(game->image, x, y, color);
		z++;
		y++;
		//x++;
	}
}

void	draw_player(t_game *game)
{
	uint32_t	color;
	int x;
	int y;

	x = 0;
	y = 0;
	color = ft_pixel( 0, 0, 0, 255);
	mlx_put_pixel(game->image, game->x_pos/ 6, game->y_pos/ 6, color);
	while (y < 3)
	{
		while (x < 3)
		{
			mlx_put_pixel(game->image, game->x_pos/ 6 + x , game->y_pos/ 6+ y, color);
			x ++;
		}
		x = 0;
		y++;
	}
}

void	draw_map(t_game *game)
{
	int x;
	int y;


	x= 0;
	y = 0;
	while (y < game->map_size_y)
	{
		while (x < ft_strlen(game->map.points[y]))
		{
			if (game->map.points[y][x] == '1')
			{
				paint_block(game, x, y, 1);
			}
			else
				paint_block(game, x, y, 0);
			x++;
		}
		x  = 0;
		y++;
	}
	draw_player(game);
}



void	get_player_position(t_game *game)
{
	game->x_pos = 0;
	game->y_pos = 0;
	game->angle = 0;
	int x;
	int y;

	x= 0;
	y = 0;
	//game->map_size_x = 24;
	//game->map_size_y = 10;
	while (y < game->map_size_y)
	{
		while (x < ft_strlen(game->map.points[y]))
		{
			if (game->map.points[y][x] == 'W')
			{
				game->x_pos = x * BLOCK_SIZE + BLOCK_SIZE / 2;
				game->y_pos = y * BLOCK_SIZE + BLOCK_SIZE / 2;
				game ->angle = PI;
			}
			if (game->map.points[y][x] == 'N')
			{
				game->x_pos = x * BLOCK_SIZE + BLOCK_SIZE / 2;
				game->y_pos = y * BLOCK_SIZE + BLOCK_SIZE / 2;
				game ->angle =PI * 1.5;
			}
			if (game->map.points[y][x] == 'E')
			{
				game->x_pos = x * BLOCK_SIZE + BLOCK_SIZE / 2;
				game->y_pos = y * BLOCK_SIZE + BLOCK_SIZE / 2;
				game ->angle = 0;
			}
			if (game->map.points[y][x] == 'S')
			{
				game->x_pos = x * BLOCK_SIZE + BLOCK_SIZE / 2;
				game->y_pos = y * BLOCK_SIZE + BLOCK_SIZE / 2;
				game ->angle = PI / 2;
			}
			x++;
		}
		x  = 0;
		y++;
	}
}

void	start_mlx(mlx_t *mlx, t_game *game)
{
	if (!mlx)
		return ;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx;
	game->image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!game->image)
		return ;
}


void get_map_size(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;

	game->map_size_x = game ->map.width;
	game->map_size_y = game ->map.height;
	return ;
	x = ft_strlen(game->map.points[0]);
	while (game->map.points[y][0])
	{
		y++;
	}
	return ;
	game->map_size_x = x - 1;
	game->map_size_y = y;
}


void load_texture(t_game *game)
{
	game->north_wall = mlx_load_png(game->map.no_text);
	game->south_wall = mlx_load_png(game->map.so_text);
	game->east_wall = mlx_load_png(game->map.ea_text);
	game->west_wall = mlx_load_png(game->map.we_text);

	if (game->north_wall == NULL || game->south_wall == NULL ||game->east_wall == NULL ||game->west_wall == NULL )
	{

		exit(1);
	}
	game->north_wall_img = mlx_texture_to_image(game->mlx, game->north_wall);
	game->south_wall_img = mlx_texture_to_image(game->mlx, game->south_wall);
	game->east_wall_img = mlx_texture_to_image(game->mlx, game->east_wall);
	game->west_wall_img = mlx_texture_to_image(game->mlx, game->west_wall);
}




int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error("Error\nInvalid number of arguments. Usage: ./cub3D <filename.cub>");
	if (check_cub_file(argv[1]) == 0)
		error("Error\nInvalid file format");
	if (!init_values(&game))
		error("Error\nFailed to initialize values");
/* 	game.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!game.mlx_ptr)
		error("Error\nFailed to initialize MLX42");
	game.win_ptr = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT);
	if (!game.win_ptr || (mlx_image_to_window(game.mlx_ptr, game.win_ptr, 0, 0) < 0))
	{
		mlx_terminate(game.mlx_ptr);
		error("Error\nFailed to create window");
	} */

	start_mlx(mlx_init(WIDTH, HEIGHT, "Cube", true), &game);
	if (mlx_image_to_window(game.mlx, game.image, 0, 0) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	printf("Loading map: %s\n", argv[1]);
	if (!parse_map(argv[1], &game))
	{
		free_map(&game);
		error("Error\nFailed to parse .cub file");
	}
	printf("Map loaded succesfully!\n");
	print_game_state(&game);
	load_texture(&game);

	get_map_size(&game);
	get_player_position(&game);
	//return (1);

	mlx_loop_hook(game.mlx, ft_hook, &game);
	//return (1);

	mlx_loop(game.mlx);
	mlx_close_window(game.mlx);
	mlx_terminate(game.mlx);
	free_map(&game);
	printf("Map closed!\n");
	return (EXIT_SUCCESS);
}
