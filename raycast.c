/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:58:18 by ttero             #+#    #+#             */
/*   Updated: 2025/01/28 19:50:23 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_start(int x, double distances[60], t_game *game)
{
	double	height;
	int		start;

	height = HEIGHT / game->raycast[x].distance;
	start = HEIGHT / 2 - height / 2;
	return (start);
}

double	calculate_end(int x, double distances[60], t_game *game)
{
	double	height;
	int		end;

	height = HEIGHT / game->raycast[x].distance;
	end = HEIGHT / 2 + height / 2;
	return (end);
}

double	calculate_step(int x, double distances[60], t_game *game)
{
	double	start;
	double	start2;
	double	step;

	if (x == 59)
		return (0);
	start = calculate_start(x, distances, game);
	start2 = calculate_start(x + 1, distances, game);
	step = (start2 - start) / ((double)WIDTH / 60);
	return (step);
}

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

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart;

	if (x >= image->width || y >= image->height)
		return (0xFF000000);
	pixelstart = image->pixels + (y * image->width + x) * sizeof(int32_t);
	return (get_rgba(*(pixelstart), *(pixelstart + 1), *(pixelstart + 2),
			*(pixelstart + 3)));
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

int	calculate_texture_x(t_game *game, int wall, double wall_x,
		mlx_image_t *texture)
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

void	draw_wall_slice(t_game *game, int start, int end, int x,
		t_texture *texture)
{
	int			y;
	int			texture_y;
	uint32_t	color;

	y = 0;
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
	double		wall_height;
	double		wall_x;

	wall_height = end - start;
	texture.texture = select_texture(game, wall);
	texture.texture_step = (double)texture.texture->height / wall_height;
	texture.texture_pos = 0;
	if (start < 0)
	{
		texture.texture_pos = -start * texture.texture_step;
		start = 0;
	}
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	wall_x = calculate_wall_x(game, wall);
	texture.texture_x = calculate_texture_x(game, wall, wall_x,
			texture.texture);
	draw_wall_slice(game, start, end, wall, &texture);
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

void	draw_view(t_game *game, double distances[60])
{
	int	x;

	double start, end;
	x = 0;
	while (x < WIDTH)
	{
		start = calculate_start(x, distances, game);
		end = calculate_end(x, distances, game);
		draw_ceiling(game, (int)start, x);
		draw_walls(game, (int)start, (int)end, x);
		draw_floor(game, (int)end, x);
		x++;
	}
	draw_map(game);
}
