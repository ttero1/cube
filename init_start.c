/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:01:16 by mjaakkol          #+#    #+#             */
/*   Updated: 2025/02/01 15:18:01 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_position(t_game *game, int x, int y, double angle)
{
	game->x_pos = x * BLOCK_SIZE + (double)BLOCK_SIZE / 2;
	game->y_pos = y * BLOCK_SIZE + (double)BLOCK_SIZE / 2;
	game->angle = angle;
}

void	check_player_direction(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map.points[y][x];
	if (tile == 'W')
		set_player_position(game, x, y, PI);
	else if (tile == 'N')
		set_player_position(game, x, y, PI * 1.5);
	else if (tile == 'E')
		set_player_position(game, x, y, 0);
	else if (tile == 'S')
		set_player_position(game, x, y, PI / 2);
}

void	get_player_position(t_game *game)
{
	size_t		x;
	int			y;
	int32_t		mouse;
	int32_t		mouse2;

	mlx_get_mouse_pos(game->mlx, &mouse, &mouse2);
	game->mouse_x = mouse;
	x = 0;
	y = 0;
	game->x_pos = 0;
	game->y_pos = 0;
	game->angle = 0;
	while (y < game->map_size_y)
	{
		while (x < ft_strlen(game->map.points[y]))
		{
			check_player_direction(game, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

void	get_map_size(t_game *game)
{
	game->map_size_x = game->map.width;
	game->map_size_y = game->map.height;
	return ;
}

void	load_texture(t_game *game)
{
	game->north_wall = mlx_load_png(game->map.no_text);
	game->south_wall = mlx_load_png(game->map.so_text);
	game->east_wall = mlx_load_png(game->map.ea_text);
	game->west_wall = mlx_load_png(game->map.we_text);
	if (game->north_wall == NULL || game->south_wall == NULL
		|| game->east_wall == NULL || game->west_wall == NULL)
	{
		free_map(game);
		mlx_terminate(game->mlx);
		error("Error\nFailed to open file");
		exit(EXIT_FAILURE);
	}
	game->north_wall_img = mlx_texture_to_image(game->mlx, game->north_wall);
	game->south_wall_img = mlx_texture_to_image(game->mlx, game->south_wall);
	game->east_wall_img = mlx_texture_to_image(game->mlx, game->east_wall);
	game->west_wall_img = mlx_texture_to_image(game->mlx, game->west_wall);
}
