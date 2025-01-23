/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:58:18 by ttero             #+#    #+#             */
/*   Updated: 2025/01/23 19:09:16 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube.h"


double calculate_start(int x, double distances[60])
{
	double height;
	int start;

	height = HEIGHT / distances[x];
	start = HEIGHT / 2 - height / 2;
	if (start < 0)
		start = 0;
	return (start);
}

double calculate_end(int x, double distances[60])
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
	double start;
	double start2;
	double step;

	//printf("W");
	if (x == 59)
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
	double start;
	double end;
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
		while (z <= WIDTH / 60)
		{
			draw_ceiling(data, start + z *step, ((double)WIDTH / 60) * x + z);
			z++;
		}
		z = 0;
		//draw_ceiling(data, start, ((double)WIDTH / 60) * x);
		while (z <= WIDTH / 60)
		{
			draw_walls(data, start + z *step, end - z * step, ((double)WIDTH / 60) * x + z);
			z++;
			//z+=100;
		}
		//mlx_put_pixel(data->image, ((double) WIDTH / 60) * x, start + y, color);
		z = 0;
		while (z <= WIDTH / 60)
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

