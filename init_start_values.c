/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:49 by mjaakkol          #+#    #+#             */
/*   Updated: 2025/01/29 15:37:47 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_values(t_game *game)
{
	game->map.points = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.no_text = NULL;
	game->map.so_text = NULL;
	game->map.we_text = NULL;
	game->map.ea_text = NULL;
	game->map.floor_color = malloc(3 * sizeof(int));
	if (!game->map.floor_color)
		return (0);
	game->map.ceiling_color = malloc(3 * sizeof(int));
	if (!game->map.ceiling_color)
	{
		free(game->map.floor_color);
		return (0);
	}
	game->map.floor_color[0] = -1;
	game->map.ceiling_color[0] = -1;
	game->player.x = -1;
	game->player.y = -1;
	game->player.player_pos = '\0';
	return (1);
}
