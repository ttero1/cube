/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:38:34 by ttero             #+#    #+#             */
/*   Updated: 2025/02/02 12:27:13 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(t_game *game)
{
	int	x;
	int	y;

	x = (game->x_pos - 0.1 + SPEED * cos(game->angle)) / BLOCK_SIZE;
	y = (game->y_pos - 0.1 + SPEED * sin(game->angle)) / BLOCK_SIZE;
	if (y >= game->map.height || y <= 0)
		return (0);
	if (x >= (int)ft_strlen(game->map.points[y]) || x <= 0)
		return (0);
	if (game->map.points[y][x] == '1' || game->map.points[y][x] == ' ')
		return (0);
	x = (game->x_pos + 0.1 + SPEED * cos(game->angle)) / BLOCK_SIZE;
	y = (game->y_pos + 0.1 + SPEED * sin(game->angle)) / BLOCK_SIZE;
	if (x >= (int)ft_strlen(game->map.points[y]) || x <= 0)
		return (0);
	if (game->map.points[y][x] == '1' || game->map.points[y][x] == ' ')
		return (0);
	return (1);
}

int	check_wall_reverse(t_game *game)
{
	int	x;
	int	y;

	x = (game->x_pos - 0.1 - SPEED * cos(game->angle)) / BLOCK_SIZE;
	y = (game->y_pos - 0.1 - SPEED * sin(game->angle)) / BLOCK_SIZE;
	if (y >= game->map.height || y <= 0)
		return (0);
	if (x >= (int)ft_strlen(game->map.points[y]) || x <= 0)
		return (0);
	if (game->map.points[y][x] == '1' || game->map.points[y][x] == ' ')
		return (0);
	x = (game->x_pos + 0.1 - SPEED * cos(game->angle)) / BLOCK_SIZE;
	y = (game->y_pos + 0.1 - SPEED * sin(game->angle)) / BLOCK_SIZE;
	if (y >= game->map.height || y <= 0)
		return (0);
	if (x >= (int)ft_strlen(game->map.points[y]) || x <= 0)
		return (0);
	if (game->map.points[y][x] == '1' || game->map.points[y][x] == ' ')
		return (0);
	return (1);
}

int	check_wall_right(t_game *game)
{
	int	x;
	int	y;

	x = (game->x_pos - 0.1 + SPEED * cos(game->angle + PI / 2)) / BLOCK_SIZE;
	y = (game->y_pos - 0.1 + SPEED * sin(game->angle + PI / 2)) / BLOCK_SIZE;
	if (y >= game->map.height || y <= 0)
		return (0);
	if (x >= (int)ft_strlen(game->map.points[y]) || x <= 0)
		return (0);
	if (game->map.points[y][x] == '1' || game->map.points[y][x] == ' ')
		return (0);
	x = (game->x_pos + 0.1 + SPEED * cos(game->angle + PI / 2)) / BLOCK_SIZE;
	y = (game->y_pos + 0.1 + SPEED * sin(game->angle + PI / 2)) / BLOCK_SIZE;
	if (y >= game->map.height || y <= 0)
		return (0);
	if (x >= (int)ft_strlen(game->map.points[y]) || x <= 0)
		return (0);
	if (game->map.points[y][x] == '1' || game->map.points[y][x] == ' ')
		return (0);
	return (1);
}

int	check_wall_left(t_game *game)
{
	int	x;
	int	y;

	x = (game->x_pos - 0.1 + SPEED * cos(game->angle - PI / 2)) / BLOCK_SIZE;
	y = (game->y_pos - 0.1 + SPEED * sin(game->angle - PI / 2)) / BLOCK_SIZE;
	if (y >= game->map.height || y <= 0)
		return (0);
	if (x >= (int)ft_strlen(game->map.points[y]) || x <= 0)
		return (0);
	if (game->map.points[y][x] == '1' || game->map.points[y][x] == ' ')
		return (0);
	x = (game->x_pos + 0.1 + SPEED * cos(game->angle - PI / 2)) / BLOCK_SIZE;
	y = (game->y_pos + 0.1 + SPEED * sin(game->angle - PI / 2)) / BLOCK_SIZE;
	if (y >= game->map.height || y <= 0)
		return (0);
	if (x >= (int)ft_strlen(game->map.points[y]) || x <= 0)
		return (0);
	if (game->map.points[y][x] == '1' || game->map.points[y][x] == ' ')
		return (0);
	return (1);
}
