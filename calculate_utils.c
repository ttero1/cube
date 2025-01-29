/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:30:50 by ttero             #+#    #+#             */
/*   Updated: 2025/01/29 11:31:01 by ttero            ###   ########.fr       */
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
			dis += 0.001;
	if (angle > PI)
		if (dis == 0)
			dis -= 0.001;
	return (dis);
}

double	calc_x_distance2(t_game *game, t_raycast *raycast, double angle)
{
	int		x;
	double	delta_x;
	double	dis;

	x = raycast->x_pos_ray / BLOCK_SIZE;
	if (angle <= PI / 2 || angle >= PI * 1.5)
		delta_x = raycast->x_pos_ray - (x + 1) * BLOCK_SIZE;
	else
		delta_x = (x)*BLOCK_SIZE - raycast->x_pos_ray;
	dis = delta_x / cos(angle);
	if (angle <= PI / 2 || angle >= PI * 1.5)
	{
		if (dis == 0)
			dis += 0.001;
	}
	else if (dis == 0)
		dis -= 0.001;
	return (dis);
}