/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:08:55 by ttero             #+#    #+#             */
/*   Updated: 2025/01/27 21:25:21 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int check_wall (t_game *game)
{
	int x;
	int y;

	x = (game->x_pos + SPEED * cos(game->angle)) / BLOCK_SIZE;
	y = (game->y_pos + SPEED * sin(game->angle)) / BLOCK_SIZE;
	if (game->map.points[y][x] == '1')
		return (0);
	return (1);
}

int check_wall_reverse (t_game *game)
{
	int x;
	int y;

	x = (game->x_pos - SPEED * cos(game->angle)) / BLOCK_SIZE;
	y = (game->y_pos - SPEED * sin(game->angle)) / BLOCK_SIZE;
	if (game->map.points[y][x] == '1')
		return (0);
	return (1);
}
int check_wall_right (t_game *game)
{
	int x;
	int y;

	x = (game->x_pos + SPEED * cos(game->angle + PI / 2)) / BLOCK_SIZE;
	y = (game->y_pos + SPEED * sin(game->angle + PI / 2)) / BLOCK_SIZE;
	if (game->map.points[y][x] == '1')
		return (0);
	return (1);
}

int check_wall_left (t_game *game)
{
	int x;
	int y;

	x = (game->x_pos + SPEED * cos(game->angle - PI / 2)) / BLOCK_SIZE;
	y = (game->y_pos + SPEED * sin(game->angle - PI / 2)) / BLOCK_SIZE;
	if (game->map.points[y][x] == '1')
		return (0);
	return (1);
}



void	ft_hook(void *param)
{
	t_game	*game;
	double	distances[60];
	double angle;

	//return ;
	game = param;
	//draw_map(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (check_wall(game))
		{
		game->x_pos += SPEED * cos(game->angle);
		game->y_pos += SPEED * sin(game->angle);
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (check_wall_reverse(game))
		{
		game->x_pos -= SPEED * cos(game->angle);
		game->y_pos -= SPEED * sin(game->angle);
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (check_wall_left(game))
		{
		game->x_pos += SPEED * cos(game->angle - PI / 2);
		game->y_pos += SPEED * sin(game->angle - PI / 2);
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (check_wall_right(game))
		{
		game->x_pos += SPEED * cos(game->angle + PI / 2);
		game->y_pos += SPEED * sin(game->angle + PI / 2);
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->angle -= SPEED_RAD;
		if (game->angle <= 0)
			game->angle +=  2 * PI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->angle += SPEED_RAD;
		if (game->angle >= 2 * PI)
			game->angle -=  2 * PI;
	}
	int x= 0;
	angle = game->angle - 30 * RAD;

	game->raycast = malloc(WIDTH * sizeof(t_raycast));
	//return ;
	while (x < WIDTH)
	{
		game->raycast[x] = calc_distance(game, angle);
		//distances[x] = calc_distance(game, angle);
		//printf("%f\n",  game->raycast[x].distance);
		x ++;
		angle += ((double)60 * RAD/ WIDTH) ;
	}

	x = 0;
	draw_view(game, distances);
	//return ;
	free (game->raycast);
	//draw_view(game, distances);


}

