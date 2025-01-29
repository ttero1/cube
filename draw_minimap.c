/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:30:42 by ttero             #+#    #+#             */
/*   Updated: 2025/01/29 15:11:43 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_colors(uint32_t *color_block, uint32_t *color_empty)
{
	*color_block = ft_pixel(200, 100, 0, 255);
	*color_empty = ft_pixel(255, 255, 255, 255);
}

void	paint_block(t_game *game, int x, int y, int flag)
{
	int			z;
	int			a;
	uint32_t	color_block;
	uint32_t	color_empty;

	init_colors(&color_block, &color_empty);
	z = -1;
	a = 0;
	x *= BLOCK_SIZE / 6;
	y *= BLOCK_SIZE / 6;
	while (z++ < BLOCK_SIZE / 6)
	{
		while (a < BLOCK_SIZE / 6)
		{
			if (flag == 1)
				mlx_put_pixel(game->image, x, y, color_block);
			else
				mlx_put_pixel(game->image, x, y, color_empty);
			a++;
			x++;
		}
		a = 0;
		x -= BLOCK_SIZE / 6;
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
	color = ft_pixel(0, 0, 0, 255);
	mlx_put_pixel(game->image, game->x_pos / 6, game->y_pos / 6, color);
	while (y < 3)
	{
		while (x < 3)
		{
			mlx_put_pixel(game->image, game->x_pos / 6 + x, game->y_pos / 6 + y,
				color);
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
