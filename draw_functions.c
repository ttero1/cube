/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:31:41 by ttero             #+#    #+#             */
/*   Updated: 2025/01/29 12:40:59 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_game *game, int start, int x)
{
	uint32_t	color;

	color = ft_pixel(game->map.ceiling_color[0], game->map.ceiling_color[1],
			game->map.ceiling_color[2], 255);
	if (start < 0)
		start = 0;
	while (start > 1)
	{
		mlx_put_pixel(game->image, x, start, color);
		start--;
	}
}

void	draw_wall_slice(t_game *game, int start, int x,
		t_texture *texture)
{
	int			y;
	int			texture_y;
	uint32_t	color;
	int 		end;

	y = 0;
	end = texture ->wall_height + start;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	while (start + y < end)
	{
		texture_y = (int)texture->texture_pos % texture->texture->height;
		color = mlx_get_pixel(texture->texture, texture->texture_x, texture_y);
		mlx_put_pixel(game->image, x, start + y, color);
		texture->texture_pos += texture->texture_step;
		y++;
	}
}

void	draw_walls(t_game *game, int start, int end, int wall)
{
	t_texture	texture;
	double		wall_x;

	texture.wall_height = end - start;
	texture.texture = select_texture(game, wall);
	texture.texture_step = (double)texture.texture->height / texture.wall_height;
	texture.texture_pos = 0;
	if (start < 0)
	{
		texture.texture_pos = -start * texture.texture_step;
		start = 0;
	}
	wall_x = calculate_wall_x(game, wall);
	texture.texture_x = calculate_texture_x(game, wall, wall_x,
			texture.texture);
	draw_wall_slice(game, start, wall, &texture);
}

void	draw_floor(t_game *game, int end, int x)
{
	uint32_t	color;

	color = ft_pixel(game->map.floor_color[0], game->map.floor_color[1],
			game->map.floor_color[2], 255);
	if (end > HEIGHT)
		end = HEIGHT - 1;
	while (end < HEIGHT - 1)
	{
		mlx_put_pixel(game->image, x, end, color);
		end++;
	}
}

void	draw_view(t_game *game)
{
	int	x;

	double start, end;
	x = 0;
	while (x < WIDTH)
	{
		start = calculate_start(x, game);
		end = calculate_end(x, game);
		draw_ceiling(game, (int)start, x);
		draw_walls(game, (int)start, (int)end, x);
		draw_floor(game, (int)end, x);
		x++;
	}
	draw_map(game);
}