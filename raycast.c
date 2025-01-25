/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:58:18 by ttero             #+#    #+#             */
/*   Updated: 2025/01/25 13:38:37 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


double calculate_start(int x, double distances[60], t_game *game)
{
	double height;
	int start;

	//height = HEIGHT / distances[x];
	height = HEIGHT / game->raycast[x].distance;
	start = HEIGHT / 2 - height / 2;
	if (start < 0)
		start = 0;
	return (start);
}

double calculate_end(int x, double distances[60], t_game *game)
{
	double height;
	int end;

	//height = HEIGHT / distances[x];
	height = HEIGHT / game->raycast[x].distance;
	end = HEIGHT / 2 + height / 2;
	if (end > HEIGHT)
		end =  HEIGHT - 1;
	return (end);
}

double calculate_step(int x, double distances[60], t_game *game)
{
	double start;
	double start2;
	double step;

	//printf("W");
	if (x == 59)
		return (0);
	start = calculate_start(x, distances, game);
	start2 = calculate_start(x + 1, distances, game);
	step = (start2 - start) / ((double) WIDTH / 60);
	return (step);
}

void draw_ceiling(t_game *game, int start, int x)
{
	uint32_t	color;

	color = ft_pixel( game->map.ceiling_color[0],
	game->map.ceiling_color[1],
	game->map.ceiling_color[2],
	255);

	while (start > 1)
	{
		mlx_put_pixel(game->image, x, start, color);
		start --;
	}
}

void draw_walls(t_game *game, int start, int end, int x, int wall)
{
	uint32_t	color;
	int y;

	color = ft_pixel( 0, 100, 100, 255 );
	if (game->raycast[wall].hit_wall == NORTH)
		color = ft_pixel( 0, 100, 100, 255 );
	if (game->raycast[wall].hit_wall == SOUTH)
		//color = ft_pixel( 0, 100, 100, 255 );
		color = ft_pixel( 200, 100, 100, 255 );
	if (game->raycast[wall].hit_wall == EAST)
		color = ft_pixel( 150, 50, 100, 255 );
	if (game->raycast[wall].hit_wall == WEST)
		color = ft_pixel( 100, 100, 200, 255 );
	y = 0;
	//color = ft_pixel( 0, 100, 100, 255 );
	while (start + y < end)
	{
		mlx_put_pixel(game->image, x, start + y, color);
		y++;
	}
}

/* void draw_floor(t_game *game, int end, int x)
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
		mlx_put_pixel(game->image, ((double)WIDTH / 60) * x, end, color);
		end ++;
	}

}
 */
void draw_floor(t_game *game, int end, int x)
{
	uint32_t	color;
	color = ft_pixel( game->map.floor_color[0],
	game->map.floor_color[1],
	game->map.floor_color[2],
	255);
	//return ;
	while (end < HEIGHT - 1)
	{
		mlx_put_pixel(game->image, x, end, color);
		end ++;
	}

}


void draw_view(t_game *game, double distances[60])
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
		//height = HEIGHT / distances[x];
		height =  HEIGHT / game->raycast[x].distance;
		//height = HEIGHT / test;
		//printf("%f\n",  game->raycast[x].distance);
		start = calculate_start(x, distances, game);
		end = calculate_end(x, distances, game);
		step = calculate_step(x, distances, game);
		//printf("%f\n",  game->raycast[x].distance);
		//printf ("%f ", height);
		while (z <= WIDTH / 60)
		{
			draw_ceiling(game, start + z *step, ((double)WIDTH / 60) * x + z);
			z++;
		}
		z = 0;
		//draw_ceiling(game, start, ((double)WIDTH / 60) * x);
		while (z <= WIDTH / 60)
		{
			draw_walls(game, start + z *step, end - z * step, ((double)WIDTH / 60) * x + z, x);
			z++;
			//z+=100;
		}
		//mlx_put_pixel(game->image, ((double) WIDTH / 60) * x, start + y, color);
		z = 0;
		while (z <= WIDTH / 60)
		{
			draw_floor(game, end - z * step, ((double)WIDTH / 60) * x + z);
			z++;
		}
		z = 0;
		//draw_floor(game, end, x);
		x++;
	}
	//return ;
	draw_map(game);
}

