/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:08:55 by ttero             #+#    #+#             */
/*   Updated: 2025/01/23 19:18:24 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


int check_wall (t_data *data)
{
	int x;
	int y;

	x = (data->x_pos + SPEED * cos(data->angle)) / BLOCK_SIZE;
	y = (data->y_pos + SPEED * sin(data->angle)) / BLOCK_SIZE;
	if (map[y][x] == 1)
		return (0);
	return (1);
}

int check_wall_reverse (t_data *data)
{
	int x;
	int y;

	x = (data->x_pos - SPEED * cos(data->angle)) / BLOCK_SIZE;
	y = (data->y_pos - SPEED * sin(data->angle)) / BLOCK_SIZE;
	if (map[y][x] == 1)
		return (0);
	return (1);
}
int check_wall_right (t_data *data)
{
	int x;
	int y;

	x = (data->x_pos + SPEED * cos(data->angle + PI / 2)) / BLOCK_SIZE;
	y = (data->y_pos + SPEED * sin(data->angle + PI / 2)) / BLOCK_SIZE;
	if (map[y][x] == 1)
		return (0);
	return (1);
}

int check_wall_left (t_data *data)
{
	int x;
	int y;

	x = (data->x_pos + SPEED * cos(data->angle - PI / 2)) / BLOCK_SIZE;
	y = (data->y_pos + SPEED * sin(data->angle - PI / 2)) / BLOCK_SIZE;
	if (map[y][x] == 1)
		return (0);
	return (1);
}



void	ft_hook(void *param)
{
	t_data	*data;
	double	distances[60];
	double angle;

	data = param;
	//draw_map(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (check_wall(data))
		{
		data->x_pos += SPEED * cos(data->angle);
		data->y_pos += SPEED * sin(data->angle);
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (check_wall_reverse(data))
		{
		data->x_pos -= SPEED * cos(data->angle);
		data->y_pos -= SPEED * sin(data->angle);
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (check_wall_left(data))
		{
		data->x_pos += SPEED * cos(data->angle - PI / 2);
		data->y_pos += SPEED * sin(data->angle - PI / 2);
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (check_wall_right(data))
		{
		data->x_pos += SPEED * cos(data->angle + PI / 2);
		data->y_pos += SPEED * sin(data->angle + PI / 2);
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->angle -= SPEED_RAD;
		if (data->angle <= 0)
			data->angle +=  2 * PI;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->angle += SPEED_RAD;
		if (data->angle >= 2 * PI)
			data->angle -=  2 * PI;
	}
	int x= 0;
	angle = data->angle - 30 * RAD;
	while (x < 60)
	{
		distances[x] = calc_distance(data, angle);
		x ++;
		angle += RAD;
	}
	draw_view(data, distances);


}

