#include "cub3d.h"

int	search_char(char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return (1);
	else
		return (0);
}

int	check_valid_char(char *line)
{
	while (*line && *line != '\n')
	{
		if (!search_char("01NSEW ", *line))
			return (0);
		line++;
	}
	return (1);
}

int	validate_player_position(t_game *game)
{
	if (game->player.x == -1 || game->player.y == -1 || game->player.player_pos == '\0')
	{
		printf("No player position found\n");
		return (0);
	}
	return (1);
}

int	check_png_file(char *file)
{
	size_t len;

	len = ft_strlen(file);
	if (len <= 4)
		return (0);
	if (strncmp(file + len - 4, ".png", 4) == 0)
		return (1);
	return (0);
}

int	parse_element(char *line, t_game *game)
{
	char	*trimmed;

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (game->map.no_text)
		{
			printf("Duplicate NO texture found\n");
			return (-1);
		}
		trimmed = ft_strtrim(line + 3, " ");
		if (!check_png_file(trimmed))
		{
			printf("No png file\n");
			free(trimmed);
			return (0);
		}
		game->map.no_text = ft_strdup(trimmed);
		free(trimmed);
		if (!game->map.no_text)
			return (-1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (game->map.so_text)
		{
			printf("Duplicate SO texture found\n");
			return (-1);
		}
		trimmed = ft_strtrim(line + 3, " ");
		if (!check_png_file(trimmed))
		{
			printf("No png file\n");
			free(trimmed);
			return (0);
		}
		game->map.so_text = ft_strdup(trimmed);
		free(trimmed);
		if (!game->map.so_text)
			return (-1);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (game->map.we_text)
		{
			printf("Duplicate WE texture found\n");
			return (-1);
		}
		trimmed = ft_strtrim(line + 3, " ");
		if (!check_png_file(trimmed))
		{
			printf("No png file\n");
			free(trimmed);
			return (0);
		}
		game->map.we_text = ft_strdup(trimmed);
		free(trimmed);
		if (!game->map.we_text)
			return (-1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (game->map.ea_text)
		{
			printf("Duplicate EA texture found\n");
			return (-1);
		}
		trimmed = ft_strtrim(line + 3, " ");
		if (!check_png_file(trimmed))
		{
			printf("No png file\n");
			free(trimmed);
			return (0);
		}
		game->map.ea_text = ft_strdup(trimmed);
		free(trimmed);
		if (!game->map.ea_text)
			return (-1);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (game->map.floor_color[0] != -1)
		{
			printf("Duplicate floor color found\n");
			return (-1);
		}
		if (!parse_color(line + 2, game->map.floor_color))
		{
			printf("Invalid floor color format\n");
			return (-1);
		}
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (game->map.ceiling_color[0] != -1)
		{
			printf("Duplicate ceiling color found\n");
			return (-1);
		}
		if (!parse_color(line + 2, game->map.ceiling_color))
		{
			printf("Invalid ceiling color format\n");
			return (-1);
		}
	}
	else
	{
		printf("Unknown element: %s\n", line);
		return (0);
	}
	printf("Success return 1 in parse_element\n");
	return (1);
}

int	parse_color(char *line, int *color)
{
	char	**rgb;
	int		i;

	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		printf("Invalid RGB format\n");
		if (rgb)
		{
			i = 0;
			while (rgb[i])
				free(rgb[i++]);
			free(rgb);
		}
		return (0);
	}
	color[0] = ft_atoi(rgb[0]);
	color[1] = ft_atoi(rgb[1]);
	color[2] = ft_atoi(rgb[2]);
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255 || color[2] < 0 || color[2] > 255)
	{
		printf("Invalid RGB color\n");
		return (0);
	}
	return (1);
}


int	validate_map(t_game *game)
{
	char	**map;
	int		y;
	int		x;
	int		row_len;
	int		next_row_len;
	int		prev_row_len;
	//int		space_top;
	//int		space_bottom;

	map = game->map.points;
	y = 0;
	//space_top = 0;
	//space_bottom = 0;
	while (y < game->map.height)
	{
		x = 0;
		row_len = ft_strlen(map[y]);
		if (y < game->map.height - 1)
			next_row_len = ft_strlen(map[y + 1]);
		if (y != 0)
			prev_row_len = ft_strlen(map[y - 1]);
		while (x < row_len && map[y][x] == ' ')
			x++;
		if (map[y][x] != '1' || map[y][row_len - 1] != '1')
		{
			printf("Row %d is not closed by walls from corners\n", y);
			return (0);
		}
		printf("%s handling this map row\n", map[y]);
		while (x < row_len)
		{
			if (map[y][x] == ' ')
			{
				//if (map[0][x])
				//	space_top = 1;
				//if (map[game->map.height - 1][x])
				//	space_bottom = 1;
				if (x > 0 && map[y][x - 1] != '1' && map[y][x - 1] != ' ')
				{
					printf("In left space not surrounded by wall\n");
					return (0);
				}
				if (x + 1 < row_len && map[y][x + 1] != '1' && map[y][x + 1] != ' ')
				{
					printf("In right space not surrounded by wall\n");
					return (0);
				}
				if (y > 0 && x < prev_row_len && map[y - 1][x] != '1' && map[y - 1][x] != ' ')
				{
					printf("In top space not surrounded by wall\n");
					return (0);
				}
				if (y < game->map.height - 1 && x < next_row_len && map[y + 1][x] != '1' && map[y - 1][x] != ' ')
				{
					printf("In bottom space not surrounded by wall\n");
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	x = 0;
	while (map[0][x] == ' ')
		x++;
	while (x < ft_strlen(map[0]))
	{
		if (map[0][x] != '1')
		{
			printf("Top row not fully walled, in %d\n", x);
			return (0);
		}
		x++;
	}
	x = 0;
	while (map[game->map.height - 1][x] == ' ')
		x++;
	while (x < ft_strlen(map[game->map.height - 1]))
	{
		if (map[game->map.height - 1][x] != '1')
		{
			printf("Bottom row not fully walled, in %d\n", x);
			return (0);
		}
		x++;
	}
	return (1);
}

void	trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';

}

int	save_line(char *line, t_game *game, int row)
{
	int	x;

	game->map.points[row] = ft_strdup(line);
	if (!game->map.points[row])
		return (0);
	x = 0;
	while (line[x])
	{
		if (ft_strchr("NSEW", line[x]))
		{
			if (game->player.x != -1)
			{
				printf("Multiple player positions found\n");
				return (0);
			}
			game->player.x = x;
			game->player.y = row;
			game->player.player_pos = line[x];
		}
		x++;
	}
	return (1);
}

int	count_map_rows(const char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Could not open file %s\n", file);
		return (-1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		printf("File %s is empty\n", file);
		close(fd);
		return (0);
	}
	while (line)
	{
		trim_newline(line);
		if (line[0] != '\0')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return(count);
}

/*int	init_map(t_map *map)
{
	map->points = NULL;
	map->width = 0;
	map->height = 0;
	map->no_text = NULL;
	map->so_text = NULL;
	map->we_text = NULL;
	map->ea_text = NULL;
	map->floor_color = malloc(3 * sizeof(int));
	if (!map->floor_color)
		return (0);
	map->ceiling_color = malloc(3 * sizeof(int));
	if (!map->ceiling_color)
	{
		free(map->floor_color);
		return (0);
	}
	map->floor_color[0] = -1;
	map->ceiling_color[0] = -1;
	return (1);
}

void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
	player->player_pos = '\0';
}*/

int	parse_map(const char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		row;
	int		map;
	int		j;
	int		len;
	int		malloc_size;

	malloc_size = count_map_rows(file);
	if (malloc_size <= 0)
		return (0);

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	row = 0;
	map = 0;
	//if (!init_map(&game->map))
	//	return (0);
	//init_player(&game->player);
	game->map.points = malloc((malloc_size + 1) * sizeof(char *));
	if (!game->map.points)
		return (0);
	j = 0;
	while (j <= malloc_size)
	{
		game->map.points[j] = NULL;
		j++;
	}
	while (line)
	{
		trim_newline(line);
		if (line[0] == '\0')
		{
			free(line);
			if (map)
				return (0);
			line = get_next_line(fd);
			continue ;
		}
		printf("%s\n", line);
		if (game->map.floor_color[0] != -1 && game->map.ceiling_color[0] != -1)
		{
			printf("Checking map\n");
			if (!check_valid_char(line))
				return (0);
		}
		if (!map && parse_element(line, game) == -1)
			return (0);
		if (!map && !parse_element(line, game))
		{
			if (!game->map.no_text || !game->map.so_text || !game->map.we_text || !game->map.ea_text)
			{
				printf("Missing texture\n");
				return (0);
			}
			map = 1;
			if (!save_line(line, game, row++))
				return (0);
		}
		else if (map)
		{
			if (!save_line(line, game, row++))
				return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!map)
	{
		printf("No map found\n");
		return (0);
	}
	game->map.height = row;
	game->map.width = 0;
	game->map.points[row] = NULL;


	j = 0;
	len = 0;
	while (j < row)
	{
		len = ft_strlen(game->map.points[j]);
		if (len > game->map.width)
			game->map.width = len;
		j++;
	}
	if (!validate_map(game))
	{
		printf("Invalid map\n");
		return (0);
	}
	if (!validate_player_position(game))
		return (0);
	return (1);
}
