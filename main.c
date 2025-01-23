/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:18 by ttero             #+#    #+#             */
/*   Updated: 2025/01/23 19:22:11 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


const char map [10][24]=
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
void paint_block(t_data *data, int x, int y, int flag)
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
				mlx_put_pixel(data->image, x, y, color_block);
			else
				mlx_put_pixel(data->image, x, y, color_empty);
			a++;
			x++;
		}
		a = 0;
		x -= BLOCK_SIZE/ 6;
		//mlx_put_pixel(data->image, x, y, color);
		z++;
		y++;
		//x++;
	}
}

void	draw_player(t_data *data)
{
	uint32_t	color;
	int x;
	int y;

	x = 0;
	y = 0;
	color = ft_pixel( 0, 0, 0, 255);
	mlx_put_pixel(data->image, data->x_pos/ 6, data->y_pos/ 6, color);
	while (y < 3)
	{
		while (x < 3)
		{
			mlx_put_pixel(data->image, data->x_pos/ 6 + x , data->y_pos/ 6+ y, color);
			x ++;
		}
		x = 0;
		y++;
	}
}

void	draw_map(t_data *data)
{
	int x;
	int y;


	x= 0;
	y = 0;
	while (y < data->map_size_y + 1)
	{
		while (x < data->map_size_x)
		{
			if (map[y][x] == 1)
			{
				paint_block(data, x, y, 1);
			}
			else
				paint_block(data, x, y, 0);
			x++;
		}
		x  = 0;
		y++;
	}
	draw_player(data);
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

void	start_mlx2(mlx_t *mlx, t_data *data2)
{
	if (!mlx)
		return ;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data2->mlx = mlx;
	data2->image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!data2->image)
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
	t_data2	data2;
	double	distances[60];
	double angle;
	int x= 0;

/* 	start_mlx2(mlx_init(WIDTH, HEIGHT, "game", true), &data2);
	if (mlx_image_to_window(data2.mlx, data2.image, 0, 0) == -1)
	{
		mlx_close_window(data2.mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
 */
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
	/* angle = data.angle - 30 * RAD;
	while (x < 60)
	{
		distances[x] = calc_distance(&data, angle);
		x ++;
		angle += RAD;
	}
	mlx_loop(data2.mlx);
	mlx_close_window(data2.mlx);
	mlx_terminate(data2.mlx); */
	mlx_loop(data.mlx);
	mlx_close_window(data.mlx);
	// mlx_delete_image(data.mlx, data.image);
	mlx_terminate(data.mlx);
	return (0);
}

