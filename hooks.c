/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:36:24 by ttero             #+#    #+#             */
/*   Updated: 2025/01/29 13:12:27 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	mouse_pos(t_game *game)
{
	int32_t	x;
	int32_t	y;

	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x > game->mouse_x)
	{
		game->angle += SPEED_RAD * (x - game->mouse_x) / 15;
		while (game->angle >= 2 * PI)
			game->angle -= 2 * PI;
	}
	if (x < game->mouse_x)
	{
		game->angle -= SPEED_RAD * (game->mouse_x - x) / 15;
		while (game->angle <= 0)
			game->angle += 2 * PI;
	}
	game->mouse_x = x;
}
