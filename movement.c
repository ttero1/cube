/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:08:55 by ttero             #+#    #+#             */
/*   Updated: 2025/02/01 15:40:39 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_raycasting(t_game *game)
{
	int		x;
	double	angle;

	x = 0;
	angle = game->angle - 30 * RAD;
	if (angle <= 0)
		angle += 2 * PI;
	game->raycast = malloc(WIDTH * sizeof(t_raycast));
	if (game->raycast == NULL)
	{
		printf("Error\nMalloc error\n");
		mlx_close_window(game->mlx);
	}
	while (x < WIDTH)
	{
		game->raycast[x] = calc_distance(game, angle);
		x++;
		angle += ((double)60 * RAD / WIDTH);
		if (angle >= 2 * PI)
			angle -= 2 * PI;
	}
}

void	ft_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	mouse_pos(game);
	handle_movement_keys(game);
	handle_rotation_keys(game);
	perform_raycasting(game);
	draw_view(game);
	free(game->raycast);
}
