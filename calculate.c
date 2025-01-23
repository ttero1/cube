/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:59:02 by ttero             #+#    #+#             */
/*   Updated: 2025/01/23 19:24:39 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube.h"

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
	 while (raycast.hit_wall == 0 && raycast.distance < 8 * BLOCK_SIZE)
	{
		cast_rays(data, &raycast, angle);
	}
	if (raycast.distance >= 8 * BLOCK_SIZE)
		raycast.distance = 9999;
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
