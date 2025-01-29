/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:58:18 by ttero             #+#    #+#             */
/*   Updated: 2025/01/29 12:40:07 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_start(int x, t_game *game)
{
	double	height;
	int		start;

	height = HEIGHT / game->raycast[x].distance;
	start = HEIGHT / 2 - height / 2;
	return (start);
}

double	calculate_end(int x, t_game *game)
{
	double	height;
	int		end;

	height = HEIGHT / game->raycast[x].distance;
	end = HEIGHT / 2 + height / 2;
	return (end);
}

mlx_image_t	*select_texture(t_game *game, int wall)
{
	if (game->raycast[wall].hit_wall == NORTH)
		return (game->north_wall_img);
	if (game->raycast[wall].hit_wall == SOUTH)
		return (game->south_wall_img);
	if (game->raycast[wall].hit_wall == EAST)
		return (game->east_wall_img);
	return (game->west_wall_img);
}

double	calculate_wall_x(t_game *game, int wall)
{
	double	wall_x;

	if (game->raycast[wall].hit_wall == NORTH
		|| game->raycast[wall].hit_wall == SOUTH)
		wall_x = game->y_pos + game->raycast[wall].distance
			* game->raycast[wall].ray_dir_y;
	else
		wall_x = game->x_pos + game->raycast[wall].distance
			* game->raycast[wall].ray_dir_x;
	return (wall_x - floor(wall_x));
}

int	calculate_texture_x(t_game *game, int wall, double wall_x, mlx_image_t *texture)
{
	int	texture_x;

	texture_x = (int)(wall_x * texture->width);
	if (((game->raycast[wall].hit_wall == NORTH
				|| game->raycast[wall].hit_wall == SOUTH)
			&& game->raycast[wall].ray_dir_x > 0)
		|| ((game->raycast[wall].hit_wall == EAST
				|| game->raycast[wall].hit_wall == WEST)
			&& game->raycast[wall].ray_dir_y < 0))
		texture_x = texture->width - texture_x - 1;
	return (texture_x);
}
