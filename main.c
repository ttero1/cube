/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:18 by ttero             #+#    #+#             */
/*   Updated: 2025/01/21 19:46:41 by ttero            ###   ########.fr       */
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

double calc_y_distance(t_data *data)
{
	int y;
	double delta_y;
	double	dis;


	y = data->y_pos / BLOCK_SIZE;
	if (data->angle <= PI)
		delta_y = data->y_pos -y * BLOCK_SIZE;
	else
		delta_y = (y + 1) * BLOCK_SIZE - data->y_pos ;
	//if (delta_y == 0)
	//	delta_y = BLOCK_SIZE;
	dis = delta_y / sin(PI - data->angle);
	//printf ("%d     %f     %f        %f \n", y, delta_y, dis, data->angle);
	//printf ("%d     %f     %f        %f \n", y, delta_y, dis, data->angle);
	return (dis);
}

double calc_x_distance(t_data *data)
{
	int x;
	double delta_x;
	double	dis;


	x = data->x_pos / BLOCK_SIZE;
	//delta_x = data->x_pos / BLOCK_SIZE - x;
	if (data->angle <= PI / 2 || data->angle >= PI * 1.5)
		delta_x = data->x_pos  - x * BLOCK_SIZE;
	else
		delta_x = (x+ 1) *BLOCK_SIZE - data->x_pos ;
	//if (delta_x == 0)
	//	delta_x = BLOCK_SIZE;
	//delta_x +=0.1;
	dis = delta_x / cos(data->angle);
	//dis = 1;
	//printf ("%d     %f     %f        %f \n", x, delta_x, dis, data->angle);
	return (dis);
}


double calc_down(t_data *data)
{
	int y;
	double delta_y;
	double	dis;


	y = data->y_pos / BLOCK_SIZE;
	delta_y = data->y_pos / BLOCK_SIZE - y;
	dis = delta_y / sin(data->angle);
	printf ("%d     %f     %f        %f \n", y, delta_y, dis, data->angle);
	return (dis);
}


double calc_left(t_data *data)
{
	int x;
	double delta_x;
	double	dis;


	x = data->x_pos / BLOCK_SIZE;
	delta_x = data->x_pos / BLOCK_SIZE - x;
	dis = delta_x / cos(PI - data->angle);
	//dis = 1;
	printf ("%d     %f     %f        %f \n", x, delta_x, dis, data->angle);
	return (dis);
}


bool check_wall2(int x, int y, t_data *data)
{
	//printf("%d   %d\n", y, x);
	//x = x -1;
	if (map[y][x] == 1)
	{
		//printf("EEE");
		return true;
	}
	return (false);
}

double calc_y_distance2(t_data *data, t_raycast *raycast, double angle)
{
	int y;
	double delta_y;
	double	dis;


	dis = 0;
	y = raycast->y_pos_ray / BLOCK_SIZE;
	if (angle <= PI)
		delta_y = raycast->y_pos_ray -(y + 1) * BLOCK_SIZE;
	else
		delta_y = (y) * BLOCK_SIZE - raycast->y_pos_ray ;
	//delta_y += 0.1;
	//printf ("%d     %f     %f        %f \n", y, delta_y, dis, data->angle);
	/* if (data->angle <= PI)
		delta_y += 0.1;
	else
		delta_y -= 0.1; */
	dis = delta_y / sin(angle);
	//printf ("%f     %d     %f     %f        %f \n",  raycast->y_pos_ray, y, delta_y, dis, data->angle);
	//printf ("%d     %f     %f        %f \n", y, delta_y, dis, data->angle);
	return (dis);
}

double calc_x_distance2(t_data *data , t_raycast *raycast, double angle)
{
	int x;
	double delta_x;
	double	dis;


	x = raycast->x_pos_ray / BLOCK_SIZE;
	//delta_x = data->x_pos / BLOCK_SIZE - x;
	if (angle <= PI / 2 || angle >= PI * 1.5)
		delta_x = raycast->x_pos_ray  - (x + 1) * BLOCK_SIZE;
	else
		delta_x = (x) *BLOCK_SIZE - raycast->x_pos_ray ;
	/* if (data->angle <= PI || data->angle >= PI * 1.5)
		delta_x -= 0.1;
	else
		delta_x += 0.1; */
	dis = delta_x / cos(angle);
	//printf ("%f    %d     %f     %f        %f \n",raycast->x_pos_ray, x, delta_x, dis, data->angle);
	//dis = 1;
	//printf ("%d     %f     %f        %f \n", x, delta_x, dis, data->angle);
	return (dis);
}


void cast_rays (t_data *data, t_raycast *raycast, double angle)
{
	double x_dis;
	double y_dis;

	x_dis = calc_x_distance2(data, raycast, angle);
	y_dis = calc_y_distance2(data, raycast, angle);
	if (fabs(x_dis) <= fabs(y_dis))
	{
		if (angle <= PI / 2 || angle >= PI * 1.5)
			{
			if (x_dis == 0)
				x_dis += 0.1;
			}
		else
			if (x_dis == 0)
				x_dis -= 0.1;
		raycast->distance += fabs(x_dis);
		raycast->x_pos_ray += fabs(x_dis) * cos(angle);
		raycast->y_pos_ray +=fabs(x_dis) * sin(angle);
		//printf("\n\nAAA%f\n\n ", x_dis);
		if (check_wall2(raycast->x_pos_ray / BLOCK_SIZE, raycast->y_pos_ray / BLOCK_SIZE, data))
		{
			raycast->hit_wall = 1;
		}
	}
	else
	{
		if (angle <= PI)
			if (y_dis == 0)
				y_dis += 0.1;
		if (angle > PI)
			if (y_dis == 0)
				y_dis -= 0.1;
		//printf("\n%f\n\n", raycast->y_pos_ray);
		raycast->distance += fabs(y_dis);
		raycast->x_pos_ray += fabs(y_dis) * cos(angle);
		raycast->y_pos_ray +=fabs(y_dis) * sin(angle);
		//printf("\n%f\n\n", raycast->y_pos_ray);
		//printf("\n\nBBB%f\n\n", y_dis);
		 if (check_wall2(raycast->x_pos_ray / BLOCK_SIZE, raycast->y_pos_ray/ BLOCK_SIZE, data))
		{
			raycast->hit_wall = 2;
		}
	}
}

double calc_distance(t_data *data, double angle)
{
	t_raycast	raycast;
	double fisheye;

	raycast.distance = 0;
	raycast.x_pos_ray = data->x_pos;
	raycast.y_pos_ray = data->y_pos;
	raycast.hit_wall = 0;

	//cast_rays(data, &raycast);
	 while (raycast.hit_wall == 0 && raycast.distance < 5 * BLOCK_SIZE)
	{
		cast_rays(data, &raycast, angle);
	}
	data->distance = raycast.distance;
	fisheye = data->angle - angle;
	if (fisheye > 2* PI)
		fisheye -= 2 * PI;
	if (fisheye < 0)
		fisheye += 2 * PI;
	raycast.distance = raycast.distance * cos(fisheye);
	//printf("%f\n", data->distance);
	return (raycast.distance);
}


int calculate_start(int x, double distances[60])
{
	double height;
	int start;

	height = HEIGHT / distances[x];
	start = HEIGHT / 2 - height / 2;
	if (start < 0)
		start = 0;
	return (start);
}

int calculate_end(int x, double distances[60])
{
	double height;
	int end;

	height = HEIGHT / distances[x];
	end = HEIGHT / 2 + height / 2;
	if (end > HEIGHT)
		end =  HEIGHT - 1;
	return (end);
}

double calculate_step(int x, double distances[60])
{
	int start;
	int start2;
	int step;

	//printf("W");
	if (x == 60)
		return (0);
	start = calculate_start(x, distances);
	start2 = calculate_start(x + 1, distances);
	step = (start2 - start) / ((double) WIDTH / 60);
	return (step);
}

void draw_ceiling(t_data *data, int start, int x)
{
	uint32_t	color;

	color = ft_pixel(
			100,
			0,
			100,
			255
			);

	while (start > 1)
	{
		mlx_put_pixel(data->image, x, start, color);
		start --;
	}
}

void draw_walls(t_data *data, int start, int end, int x)
{
	uint32_t	color;
	int y;

	color = ft_pixel( 0, 100, 100, 255 );
	while (start + y < end)
	{
		mlx_put_pixel(data->image, x, start + y, color);
		y++;
	}
}

/* void draw_floor(t_data *data, int end, int x)
{
	uint32_t	color;
	color = ft_pixel(
			100,
			0,
			0,
			255
			);
	while (end < HEIGHT - 1)
	{
		mlx_put_pixel(data->image, ((double)WIDTH / 60) * x, end, color);
		end ++;
	}

}
 */
void draw_floor(t_data *data, int end, int x)
{
	uint32_t	color;
	color = ft_pixel(
			100,
			0,
			0,
			255
			);
	while (end < HEIGHT - 1)
	{
		mlx_put_pixel(data->image, x, end, color);
		end ++;
	}

}


void draw_view(t_data *data, double distances[60])
{
	int x;
	double height;
	int start;
	int end;
	double step;
	int y;
	int z;
	uint32_t	color;
	color = ft_pixel( 0, 100, 100, 255 );

	x = 0;
	z = 0;
	while (x < 60)
	{
		y = 0;
		height = HEIGHT / distances[x];
		start = calculate_start(x, distances);
		end = calculate_end(x, distances);
		step = calculate_step(x, distances);
		//printf ("%d ", step);
		while (z < WIDTH / 60)
		{
			draw_ceiling(data, start + z *step, ((double)WIDTH / 60) * x + z);
			z++;
		}
		z = 0;
		//draw_ceiling(data, start, ((double)WIDTH / 60) * x);
		while (z < WIDTH / 60)
		{
			draw_walls(data, start + z *step, end - z * step, ((double)WIDTH / 60) * x + z);
			z++;
			//z+=100;
		}
		//mlx_put_pixel(data->image, ((double) WIDTH / 60) * x, start + y, color);
		z = 0;
		while (z < WIDTH / 60)
		{
			draw_floor(data, end - z * step, ((double)WIDTH / 60) * x + z);
			z++;
		}
		z = 0;
		//draw_floor(data, end, x);
		x++;
	}
	draw_map(data);

}


/* void draw_view(t_data *data, double distances[60])
{
	int x;
	double height;
	int start;
	int end;
	double step;
	int y;
	uint32_t	color;
	color = ft_pixel( 0, 100, 100, 255 );

	x = 0;
	while (x < 60)
	{
		y = 0;
		height = HEIGHT / distances[x];
		start = calculate_start(x, distances);
		end = calculate_end(x, distances);
		step = calculate_step(x, distances);
		//printf ("%d ", step);
		draw_ceiling(data, start, ((double)WIDTH / 60) * x);
		draw_walls(data, start, end, ((double)WIDTH / 60) * x);
		while (start + y < end)
		{
			mlx_put_pixel(data->image, ((double) WIDTH / 60) * x, start + y, color);
			y++;
		}
		draw_floor(data, end, x);
		x++;
	}
	draw_map(data);

}
 */
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
	/* uint32_t	color;

	color = ft_pixel(
			100,
			100,
			100,
			255
			); */
	//mlx_put_pixel(data->image, data->x_pos, data->y_pos, color);
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

