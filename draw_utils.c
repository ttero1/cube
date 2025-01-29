/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:34:24 by ttero             #+#    #+#             */
/*   Updated: 2025/01/29 14:50:06 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart;

	if (x >= image->width || y >= image->height)
		return (0xFF000000);
	pixelstart = image->pixels + (y * image->width + x) * sizeof(int32_t);
	return (ft_pixel(*(pixelstart), *(pixelstart + 1), *(pixelstart + 2),
			*(pixelstart + 3)));
}

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
