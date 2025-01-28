/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:59:02 by ttero             #+#    #+#             */
/*   Updated: 2025/01/28 18:16:27 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_wall2(int x, int y, t_game *game)
{
	if (game->map.points[y][x] == '1' || game->map.points[y][x] == ' ')
	{
		return (true);
	}
	return (false);
}

double	calc_y_distance2(t_game *game, t_raycast *raycast, double angle)
{
	int		y;
	double	delta_y;
	double	dis;

	dis = 0;
	y = raycast->y_pos_ray / BLOCK_SIZE;
	if (angle <= PI)
		delta_y = raycast->y_pos_ray - (y + 1) * BLOCK_SIZE;
	else
		delta_y = (y)*BLOCK_SIZE - raycast->y_pos_ray;
	dis = delta_y / sin(angle);
	if (angle <= PI)
		if (dis == 0)
			dis += 0.01;
	if (angle > PI)
		if (dis == 0)
			dis -= 0.01;
	return (dis);
}

double	calc_x_distance2(t_game *game, t_raycast *raycast, double angle)
{
	int		x;
	double	delta_x;
	double	dis;

	x = raycast->x_pos_ray / BLOCK_SIZE;
	// delta_x = game->x_pos / BLOCK_SIZE - x;
	if (angle <= PI / 2 || angle >= PI * 1.5)
		delta_x = raycast->x_pos_ray - (x + 1) * BLOCK_SIZE;
	else
		delta_x = (x)*BLOCK_SIZE - raycast->x_pos_ray;
	dis = delta_x / cos(angle);
	if (angle <= PI / 2 || angle >= PI * 1.5)
	{
		if (dis == 0)
			dis += 0.01;
	}
	else if (dis == 0)
		dis -= 0.01;
	return (dis);
}

void	update_raycast_x(t_game *game, t_raycast *raycast, double angle,
		double x_dis)
{
	raycast->distance += fabs(x_dis);
	raycast->x_pos_ray += fabs(x_dis) * cos(angle);
	raycast->y_pos_ray += fabs(x_dis) * sin(angle);
	if (check_wall2(raycast->x_pos_ray / BLOCK_SIZE, raycast->y_pos_ray
			/ BLOCK_SIZE, game))
	{
		if (angle <= PI / 2 || angle >= PI * 1.5)
			raycast->hit_wall = WEST;
		else
			raycast->hit_wall = EAST;
	}
}

void	update_raycast_y(t_game *game, t_raycast *raycast, double angle,
		double y_dis)
{
	raycast->distance += fabs(y_dis);
	raycast->x_pos_ray += fabs(y_dis) * cos(angle);
	raycast->y_pos_ray += fabs(y_dis) * sin(angle);
	if (check_wall2(raycast->x_pos_ray / BLOCK_SIZE, raycast->y_pos_ray
			/ BLOCK_SIZE, game))
	{
		if (angle <= PI)
			raycast->hit_wall = NORTH;
		else
			raycast->hit_wall = SOUTH;
	}
}

void	cast_rays(t_game *game, t_raycast *raycast, double angle)
{
	double	x_dis;
	double	y_dis;

	x_dis = calc_x_distance2(game, raycast, angle);
	y_dis = calc_y_distance2(game, raycast, angle);
	if (fabs(x_dis) <= fabs(y_dis))
	{
		update_raycast_x(game, raycast, angle, x_dis);
	}
	else
	{
		update_raycast_y(game, raycast, angle, y_dis);
	}
}

t_raycast	calc_distance(t_game *game, double angle)
{
	t_raycast	raycast;
	double		fisheye;

	raycast.distance;
	raycast.x_pos_ray = game->x_pos;
	raycast.y_pos_ray = game->y_pos;
	raycast.hit_wall = -1;
	raycast.distance = 0;
	while (raycast.hit_wall == -1 && raycast.distance < 8 * BLOCK_SIZE)
	{
		cast_rays(game, &raycast, angle);
	}
	if (raycast.distance >= 8 * BLOCK_SIZE)
		raycast.distance = 9999;
	game->distance = raycast.distance;
	fisheye = game->angle - angle;
	if (fisheye > 2 * PI)
		fisheye -= 2 * PI;
	if (fisheye < 0)
		fisheye += 2 * PI;
	raycast.distance = raycast.distance * cos(fisheye);
	raycast.ray_dir_x = sin(angle);
	raycast.ray_dir_y = cos(angle);
	return (raycast);
}
