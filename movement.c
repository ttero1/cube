/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:08:55 by ttero             #+#    #+#             */
/*   Updated: 2025/01/29 09:07:29 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(t_game *game)
{
	int	x;
	int	y;

	x = (game->x_pos + SPEED * cos(game->angle)) / BLOCK_SIZE;
	y = (game->y_pos + SPEED * sin(game->angle)) / BLOCK_SIZE;
	if (game->map.points[y][x] == '1')
		return (0);
	return (1);
}

int	check_wall_reverse(t_game *game)
{
	int	x;
	int	y;

	x = (game->x_pos - SPEED * cos(game->angle)) / BLOCK_SIZE;
	y = (game->y_pos - SPEED * sin(game->angle)) / BLOCK_SIZE;
	if (game->map.points[y][x] == '1')
		return (0);
	return (1);
}

int	check_wall_right(t_game *game)
{
	int	x;
	int	y;

	x = (game->x_pos + SPEED * cos(game->angle + PI / 2)) / BLOCK_SIZE;
	y = (game->y_pos + SPEED * sin(game->angle + PI / 2)) / BLOCK_SIZE;
	if (game->map.points[y][x] == '1')
		return (0);
	return (1);
}

int	check_wall_left(t_game *game)
{
	int	x;
	int	y;

	x = (game->x_pos + SPEED * cos(game->angle - PI / 2)) / BLOCK_SIZE;
	y = (game->y_pos + SPEED * sin(game->angle - PI / 2)) / BLOCK_SIZE;
	if (game->map.points[y][x] == '1')
		return (0);
	return (1);
}

void	handle_movement_keys(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) && check_wall(game))
	{
		game->x_pos += SPEED * cos(game->angle);
		game->y_pos += SPEED * sin(game->angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) && check_wall_reverse(game))
	{
		game->x_pos -= SPEED * cos(game->angle);
		game->y_pos -= SPEED * sin(game->angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A) && check_wall_left(game))
	{
		game->x_pos += SPEED * cos(game->angle - PI / 2);
		game->y_pos += SPEED * sin(game->angle - PI / 2);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D) && check_wall_right(game))
	{
		game->x_pos += SPEED * cos(game->angle + PI / 2);
		game->y_pos += SPEED * sin(game->angle + PI / 2);
	}
}

void	handle_rotation_keys(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->angle -= SPEED_RAD;
		if (game->angle <= 0)
			game->angle += 2 * PI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->angle += SPEED_RAD;
		if (game->angle >= 2 * PI)
			game->angle -= 2 * PI;
	}
}

void	perform_raycasting(t_game *game)
{
	int		x;
	double	angle;

	x = 0;
	angle = game->angle - 30 * RAD;
	game->raycast = malloc(WIDTH * sizeof(t_raycast));
	while (x < WIDTH)
	{
		game->raycast[x] = calc_distance(game, angle);
		x++;
		angle += ((double)60 * RAD / WIDTH);
	}
}

static void	mouse_pos(t_game *game)
{
	int32_t	x;
	int32_t	y;

	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x > game->mouse_x)
	{
		game->angle += SPEED_RAD;
		while (game->angle >= 2 * PI)
			game->angle -= 2 * PI;
	}
	if (x < game->mouse_x)
	{
		game->angle -= SPEED_RAD;
		while (game->angle <= 0)
			game->angle += 2 * PI;
	}
	game->mouse_x = x;
}



void	ft_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	mouse_pos(game);
	handle_movement_keys(game);
	handle_rotation_keys(game);
	perform_raycasting(game);
	draw_view(game, NULL);
	free(game->raycast);
}
