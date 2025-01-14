/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:18 by ttero             #+#    #+#             */
/*   Updated: 2025/01/14 15:25:07 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


char map [10][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,'E',0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
void paint_block(t_data *data, int x, int y)
{
	int z;
	int a;
	uint32_t	color;
	color = ft_pixel(
			200,
			100,
			0,
			255
			);
	z = 0;
	a = 0;
	x *= BLOCK_SIZE;
	y *= BLOCK_SIZE;
	while (z < BLOCK_SIZE)
	{
		while (a < BLOCK_SIZE)
		{
			mlx_put_pixel(data->image, x, y, color);
			a++;
			x++;
		}
		a = 0;
		x -= BLOCK_SIZE;
		//mlx_put_pixel(data->image, x, y, color);
		z++;
		y++;
		//x++;
	}
}

void	draw_map(t_data *data)
{
	int x;
	int y;

	x= 0;
	y = 0;
	while (y < data->map_size_y)
	{
		while (x < data->map_size_x)
		{
			if (map[y][x] == 1)
			{
				paint_block(data, x, y);
			}
			x++;
		}
		x  = 0;
		y++;
	}
}

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

void calc_left(t_data *data)
{
	int x;
	double delta_x;
	double	dis;


	x = data->x_pos / BLOCK_SIZE;
	delta_x = data->x_pos / BLOCK_SIZE - x;
	dis = delta_x / cos(PI - data->angle);
	//dis = 1;
	printf ("%d     %f     %f        %f \n", x, delta_x, dis, data->angle);
}

void calc_right(t_data *data)
{
	int x;
	double delta_x;
	double	dis;


	x = data->x_pos / BLOCK_SIZE;
	delta_x = data->x_pos / BLOCK_SIZE - x;
	dis = delta_x / cos(data->angle);
	//dis = 1;
	printf ("%d     %f     %f        %f \n", x, delta_x, dis, data->angle);
}


void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	draw_map(data);
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
	/* if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->angle -= SPEED_RAD;
		if (data->angle >= 2 * PI)
			data->angle +=  2 * PI;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->angle += SPEED_RAD;
		if (data->angle <= 2 * PI)
			data->angle -=  2 * PI;
	} */
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
	//printf("%f\n", data->angle);
	uint32_t	color;
	
	color = ft_pixel(
			100,
			100,
			100,
			255
			);
	mlx_put_pixel(data->image, data->x_pos, data->y_pos, color);
	if (data->angle > PI /2 && data->angle < PI * 1.5)
		calc_left(data);
	else	
		calc_right(data);
}

void	get_player_position(t_data *data)
{
	data->x_pos = 0;
	data->y_pos = 0;
	data->angle = 0;
	int x;
	int y;

	x= 0;
	y = 0;
	//data->map_size_x = 24;
	//data->map_size_y = 10;
	while (y < data->map_size_y)
	{
		while (x < data->map_size_x)
		{
			if (map[y][x] == 'W')
			{
				data->x_pos = x * BLOCK_SIZE + BLOCK_SIZE / 2;
				data->y_pos = y * BLOCK_SIZE + BLOCK_SIZE / 2;
				data ->angle = PI;
			}
			if (map[y][x] == 'N')
			{
				data->x_pos = x * BLOCK_SIZE + BLOCK_SIZE / 2;
				data->y_pos = y * BLOCK_SIZE + BLOCK_SIZE / 2;
				data ->angle =PI * 1.5;
			}
			if (map[y][x] == 'E')
			{
				data->x_pos = x * BLOCK_SIZE + BLOCK_SIZE / 2;
				data->y_pos = y * BLOCK_SIZE + BLOCK_SIZE / 2;
				data ->angle = 0;
			}
			if (map[y][x] == 'S')
			{
				data->x_pos = x * BLOCK_SIZE + BLOCK_SIZE / 2;
				data->y_pos = y * BLOCK_SIZE + BLOCK_SIZE / 2;
				data ->angle = PI / 2;
			}
			x++;
		}
		x  = 0;
		y++;
	}
}

void	start_mlx(mlx_t *mlx, t_data *data)
{
	if (!mlx)
		return ;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->mlx = mlx;
	data->image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!data->image)
		return ;
}
void get_map_size(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	x = ft_strlen(map[0]);
	while (map[y][0])
	{
		y++;
	}
	data->map_size_x = x - 1;
	data->map_size_y = y;
}


int32_t	main()
{
	t_data	data;

	get_map_size(&data);
	get_player_position(&data);
	start_mlx(mlx_init(WIDTH, HEIGHT, "Cube", true), &data);
	if (mlx_image_to_window(data.mlx, data.image, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	mlx_loop_hook(data.mlx, ft_hook, &data);
	//printf("AAA");
	//mlx_scroll_hook(data.mlx, &my_scrollhook, &data);
	mlx_loop(data.mlx);
	mlx_close_window(data.mlx);
	// mlx_delete_image(data.mlx, data.image);
	mlx_terminate(data.mlx);
	return (0);
}

