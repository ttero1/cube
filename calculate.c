/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:59:02 by ttero             #+#    #+#             */
/*   Updated: 2025/01/27 22:48:10 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

double calc_y_distance(t_game *game)
{
	int y;
	double delta_y;
	double	dis;


	y = game->y_pos / BLOCK_SIZE;
	if (game->angle <= PI)
		delta_y = game->y_pos -y * BLOCK_SIZE;
	else
		delta_y = (y + 1) * BLOCK_SIZE - game->y_pos ;
	//if (delta_y == 0)
	//	delta_y = BLOCK_SIZE;
	dis = delta_y / sin(PI - game->angle);
	//printf ("%d     %f     %f        %f \n", y, delta_y, dis, game->angle);
	//printf ("%d     %f     %f        %f \n", y, delta_y, dis, game->angle);
	return (dis);
}

double calc_x_distance(t_game *game)
{
	int x;
	double delta_x;
	double	dis;


	x = game->x_pos / BLOCK_SIZE;
	//delta_x = game->x_pos / BLOCK_SIZE - x;
	if (game->angle <= PI / 2 || game->angle >= PI * 1.5)
		delta_x = game->x_pos  - x * BLOCK_SIZE;
	else
		delta_x = (x+ 1) *BLOCK_SIZE - game->x_pos ;
	//if (delta_x == 0)
	//	delta_x = BLOCK_SIZE;
	//delta_x +=0.1;
	dis = delta_x / cos(game->angle);
	//dis = 1;
	//printf ("%d     %f     %f        %f \n", x, delta_x, dis, game->angle);
	return (dis);
}


double calc_down(t_game *game)
{
	int y;
	double delta_y;
	double	dis;


	y = game->y_pos / BLOCK_SIZE;
	delta_y = game->y_pos / BLOCK_SIZE - y;
	dis = delta_y / sin(game->angle);
	printf ("%d     %f     %f        %f \n", y, delta_y, dis, game->angle);
	return (dis);
}


double calc_left(t_game *game)
{
	int x;
	double delta_x;
	double	dis;


	x = game->x_pos / BLOCK_SIZE;
	delta_x = game->x_pos / BLOCK_SIZE - x;
	dis = delta_x / cos(PI - game->angle);
	//dis = 1;
	printf ("%d     %f     %f        %f \n", x, delta_x, dis, game->angle);
	return (dis);
}


bool check_wall2(int x, int y, t_game *game)
{
	//printf("%d   %d\n", y, x);
	//x = x -1;
	if (game->map.points[y][x] == '1')
	{
		//printf("EEE");
		return true;
	}
	return (false);
}

double calc_y_distance2(t_game *game, t_raycast *raycast, double angle)
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
	//printf ("%d     %f     %f        %f \n", y, delta_y, dis, game->angle);
	/* if (game->angle <= PI)
		delta_y += 0.1;
	else
		delta_y -= 0.1; */
	dis = delta_y / sin(angle);
	//printf ("%f     %d     %f     %f        %f \n",  raycast->y_pos_ray, y, delta_y, dis, game->angle);
	//printf ("%d     %f     %f        %f \n", y, delta_y, dis, game->angle);
	return (dis);
}

double calc_x_distance2(t_game *game , t_raycast *raycast, double angle)
{
	int x;
	double delta_x;
	double	dis;


	x = raycast->x_pos_ray / BLOCK_SIZE;
	//delta_x = game->x_pos / BLOCK_SIZE - x;
	if (angle <= PI / 2 || angle >= PI * 1.5)
		delta_x = raycast->x_pos_ray  - (x + 1) * BLOCK_SIZE;
	else
		delta_x = (x) *BLOCK_SIZE - raycast->x_pos_ray ;
	/* if (game->angle <= PI || game->angle >= PI * 1.5)
		delta_x -= 0.1;
	else
		delta_x += 0.1; */
	dis = delta_x / cos(angle);
	//printf ("%f    %d     %f     %f        %f \n",raycast->x_pos_ray, x, delta_x, dis, game->angle);
	//dis = 1;
	//printf ("%d     %f     %f        %f \n", x, delta_x, dis, game->angle);
	return (dis);
}


void cast_rays (t_game *game, t_raycast *raycast, double angle)
{
	double x_dis;
	double y_dis;

	x_dis = calc_x_distance2(game, raycast, angle);
	y_dis = calc_y_distance2(game, raycast, angle);
	if (fabs(x_dis) <= fabs(y_dis))
	{
		if (angle <= PI / 2 || angle >= PI * 1.5)
			{
			if (x_dis == 0)
				x_dis += 0.01;
			}
		else
			if (x_dis == 0)
				x_dis -= 0.01;
		raycast->distance += fabs(x_dis);
		raycast->x_pos_ray += fabs(x_dis) * cos(angle);
		raycast->y_pos_ray +=fabs(x_dis) * sin(angle);
		//printf("\n\nAAA%f\n\n ", x_dis);
		if (check_wall2(raycast->x_pos_ray / BLOCK_SIZE, raycast->y_pos_ray / BLOCK_SIZE, game))
		{
			if (angle <= PI / 2 || angle >= PI * 1.5)
				raycast->hit_wall = WEST;
			else
				raycast->hit_wall = EAST;
		}
	}
	else
	{
		if (angle <= PI)
			if (y_dis == 0)
				y_dis += 0.01;
		if (angle > PI)
			if (y_dis == 0)
				y_dis -= 0.01;
		//printf("\n%f\n\n", raycast->y_pos_ray);
		raycast->distance += fabs(y_dis);
		raycast->x_pos_ray += fabs(y_dis) * cos(angle);
		raycast->y_pos_ray +=fabs(y_dis) * sin(angle);
		//printf("\n%f\n\n", raycast->y_pos_ray);
		//printf("\n\nBBB%f\n\n", y_dis);
		 if (check_wall2(raycast->x_pos_ray / BLOCK_SIZE, raycast->y_pos_ray/ BLOCK_SIZE, game))
		{
			if (angle <= PI)
				raycast->hit_wall = NORTH;
			else
				raycast->hit_wall = SOUTH;
		}
	}
}


t_raycast calc_distance(t_game *game, double angle)
{
	t_raycast	raycast;
	double fisheye;

	raycast.distance = 0;
	raycast.x_pos_ray = game->x_pos;
	raycast.y_pos_ray = game->y_pos;
	raycast.hit_wall = -1;

	//cast_rays(game, &raycast);
	//printf ("\n\n %f    %f    %f", raycast.x_pos_ray, raycast.y_pos_ray, angle);
	 while (raycast.hit_wall == -1 && raycast.distance < 8 * BLOCK_SIZE)
	{
		cast_rays(game, &raycast, angle);
		//return ;
	}
	//return ;
	if (raycast.distance >= 8 * BLOCK_SIZE)
		raycast.distance = 9999;
	game->distance = raycast.distance;
	fisheye = game->angle - angle;
	if (fisheye > 2* PI)
		fisheye -= 2 * PI;
	if (fisheye < 0)
		fisheye += 2 * PI;
	raycast.distance = raycast.distance * cos(fisheye);
	raycast.ray_dir_x = sin(angle) ;
	raycast.ray_dir_y = cos(angle) ;
	//printf ("%f              %f     %f\n", raycast.ray_dir_x, raycast.ray_dir_y, raycast.distance);
	//printf("%f\n", game->distance);
	return (raycast);
}

