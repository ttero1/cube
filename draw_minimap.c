/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:30:42 by ttero             #+#    #+#             */
/*   Updated: 2025/02/03 10:40:45 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_block_values(uint32_t *color_block, uint32_t *color_empty,
	int *z, int *a)
{
	*color_block = ft_pixel(200, 100, 0, 255);
	*color_empty = ft_pixel(255, 255, 255, 255);
	*z = -1;
	*a = 0;
}

void	paint_block(t_game *game, int x, int y, int flag)
{
	int			z;
	int			a;
	uint32_t	color_block;
	uint32_t	color_empty;

	init_block_values(&color_block, &color_empty, &z, &a);
	x *= 5;
	y *= 5;
	if (x > WIDTH / 2 || y > HEIGHT / 2)
		return ;
	while (z++ < 5)
	{
		while (a < 5)
		{
			if (flag == 1)
				mlx_put_pixel(game->image, x, y, color_block);
			else
				mlx_put_pixel(game->image, x, y, color_empty);
			a++;
			x++;
		}
		a = 0;
		x -= 5;
		y++;
	}
}

void	draw_player(t_game *game)
{
	uint32_t	color;
	int			x;
	int			y;

	x = 0;
	y = 0;
	if (game->x_pos * 5 / BLOCK_SIZE > WIDTH / 2
		|| game->y_pos * 5 / BLOCK_SIZE > HEIGHT / 2)
		return ;
	color = ft_pixel(0, 0, 0, 255);
	while (y < 3)
	{
		while (x < 3)
		{
			mlx_put_pixel(game->image, game->x_pos * 5 / BLOCK_SIZE + x,
				game->y_pos * 5 / BLOCK_SIZE + y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->map_size_y)
	{
		while (x < (int)ft_strlen(game->map.points[y]))
		{
			if (game->map.points[y][x] == '1')
			{
				paint_block(game, x, y, 1);
			}
			else
				paint_block(game, x, y, 0);
			x++;
		}
		x = 0;
		y++;
	}
	draw_player(game);
}
