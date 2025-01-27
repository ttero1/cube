/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:58:18 by ttero             #+#    #+#             */
/*   Updated: 2025/01/27 22:54:04 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


double calculate_start(int x, double distances[60], t_game *game)
{
	double height;
	int start;

	//height = HEIGHT / distances[x];
	height = HEIGHT / game->raycast[x].distance;
	start = HEIGHT / 2 - height / 2;
	if (start < 0)
		start = 0;
	return (start);
}

double calculate_end(int x, double distances[60], t_game *game)
{
	double height;
	int end;

	//height = HEIGHT / distances[x];
	height = HEIGHT / game->raycast[x].distance;
	end = HEIGHT / 2 + height / 2;
	if (end > HEIGHT)
		end =  HEIGHT - 1;
	return (end);
}

double calculate_step(int x, double distances[60], t_game *game)
{
	double start;
	double start2;
	double step;

	//printf("W");
	if (x == 59)
		return (0);
	start = calculate_start(x, distances, game);
	start2 = calculate_start(x + 1, distances, game);
	step = (start2 - start) / ((double) WIDTH / 60);
	return (step);
}

void draw_ceiling(t_game *game, int start, int x)
{
	uint32_t	color;

	color = ft_pixel( game->map.ceiling_color[0],
	game->map.ceiling_color[1],
	game->map.ceiling_color[2],
	255);

	while (start > 1)
	{
		mlx_put_pixel(game->image, x, start, color);
		start --;
	}
}

/*  void draw_walls(t_game *game, int start, int end, int x, int wall)
{
	uint32_t	color;
	int y;

	color = ft_pixel( 0, 100, 100, 255 );
	if (game->raycast[wall].hit_wall == NORTH)
		color = ft_pixel( 0, 100, 100, 255 );
	if (game->raycast[wall].hit_wall == SOUTH)
		//color = ft_pixel( 0, 100, 100, 255 );
		color = ft_pixel( 200, 100, 100, 255 );
	if (game->raycast[wall].hit_wall == EAST)
		color = ft_pixel( 150, 50, 100, 255 );
	if (game->raycast[wall].hit_wall == WEST)
		color = ft_pixel( 100, 100, 200, 255 );
	y = 0;
	//color = ft_pixel( 0, 100, 100, 255 );
	while (start + y < end)
	{
		mlx_put_pixel(game->image, x, start + y, color);
		y++;
	}
}
 */

static int get_rgba(int r, int g, int b, int a)
{
  return (r << 24 | g << 16 | b << 8 | a);
}


#define BPP sizeof(int32_t)

int32_t mlx_get_pixel(mlx_image_t* image, uint32_t x, uint32_t y) {
  if (x >= image->width || y >= image->height)
    return 0xFF000000;
  uint8_t* pixelstart = image->pixels + (y * image->width + x) * BPP;
  return get_rgba(*(pixelstart), *(pixelstart + 1),
    * (pixelstart + 2), *(pixelstart + 3));
}

# define TEXTURE_HEIGHT 64
# define TEXTURE_WIDTH 64

  void draw_walls(t_game *game, int start, int end, int x, int wall)
{
    int y = 0;
    int texture_x, texture_y;
    double wall_height = end - start;
    double texture_step = (double)TEXTURE_HEIGHT / fmax(wall_height, 1);
	double texture_pos = 0;


	mlx_image_t *texture;
	if (game->raycast[wall].hit_wall == NORTH)
    	texture = game->north_wall_img;
	else if (game->raycast[wall].hit_wall == SOUTH)
    	texture = game->south_wall_img;
	else if (game->raycast[wall].hit_wall == EAST)
    	texture = game->east_wall_img;
	else
    	texture = game->west_wall_img;

    double wall_x;
    if (game->raycast[wall].hit_wall == NORTH || game->raycast[wall].hit_wall == SOUTH)
        wall_x = game->y_pos + game->raycast[wall].distance * game->raycast[wall].ray_dir_y;
    else // Horizontal hit
        wall_x = game->x_pos + game->raycast[wall].distance * game->raycast[wall].ray_dir_x;


	/* if (wall == 399)
	{
		printf("%f  %f   %f    %f\n", game->y_pos, game->raycast[wall].distance, game->raycast[wall].ray_dir_y, wall_x);
	} */
	wall_x -= floor(wall_x);
	if (wall_x > 0.99)
		wall_x = 0;
	//printf("%d     %f\n",wall,  wall_x);
    texture_x = (int)(wall_x * TEXTURE_WIDTH);
	//printf("%d\n\n", texture_x);
	/* if (wall == 399)
	{
		printf("%f  %f   %f    %f\n\n", game->y_pos, game->raycast[wall].distance, game->raycast[wall].ray_dir_y, wall_x);
	} */
	//printf("Wall: %d, Wall X: %f, Texture X: %d\n", wall, wall_x, texture_x);

    if (((game->raycast[wall].hit_wall == NORTH || game->raycast[wall].hit_wall == SOUTH) && game->raycast[wall].ray_dir_x > 0) ||
        ((game->raycast[wall].hit_wall == EAST || game->raycast[wall].hit_wall == WEST)&& game->raycast[wall].ray_dir_y < 0))
        texture_x = TEXTURE_WIDTH - texture_x - 1;


    while (start + y < end)
    {
        texture_y = (int)texture_pos % TEXTURE_HEIGHT;
		//printf("      %d\n", texture_y);
        uint32_t color = mlx_get_pixel(texture, texture_x, texture_y);
        mlx_put_pixel(game->image, x, start + y, color);
        texture_pos += texture_step;
        y++;
    }
}


void draw_floor(t_game *game, int end, int x)
{
	uint32_t	color;
	color = ft_pixel( game->map.floor_color[0],
	game->map.floor_color[1],
	game->map.floor_color[2],
	255);
	//return ;
	while (end < HEIGHT - 1)
	{
		mlx_put_pixel(game->image, x, end, color);
		end ++;
	}

}


void draw_view(t_game *game, double distances[60])
{
    int x;
    double start, end;

    x = 0;
    while (x < WIDTH) // Loop through all vertical slices
    {
        // Calculate start and end of the wall slice for the current ray
        start = calculate_start(x, distances, game);
        end = calculate_end(x, distances, game);

        // Draw ceiling
        draw_ceiling(game, (int)start, x * (WIDTH / WIDTH));

        // Draw wall slice (single call, no fragmentation)
        draw_walls(game, (int)start, (int)end, x * (WIDTH / WIDTH), x);

        // Draw floor
        draw_floor(game, (int)end, x * (WIDTH / WIDTH));

        x++;
    }

    // Draw the map overlay
    draw_map(game);
}
