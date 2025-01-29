/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:54:16 by mjaakkol          #+#    #+#             */
/*   Updated: 2025/01/29 13:54:42 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *error_message)
{
	printf("%s\n", error_message);
	exit(EXIT_FAILURE);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.points)
	{
		while (game->map.points[i])
		{
			free(game->map.points[i]);
			i++;
		}
		free(game->map.points);
	}
	if (game->map.no_text)
		free(game->map.no_text);
	if (game->map.so_text)
		free(game->map.so_text);
	if (game->map.ea_text)
		free(game->map.ea_text);
	if (game->map.we_text)
		free(game->map.we_text);
	if (game->map.floor_color)
		free(game->map.floor_color);
	if (game->map.ceiling_color)
		free(game->map.ceiling_color);
}
