/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:50:26 by mjaakkol          #+#    #+#             */
/*   Updated: 2025/01/29 10:57:35 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_player_position(t_game *game)
{
	if (game->player.x == -1 || game->player.y == -1 \
			|| game->player.player_pos == '\0')
		return (0);
	return (1);
}

int	validate_row_edges(char *row, int row_index)
{
	int	len;
	int	x;

	x = 0;
	len = ft_strlen(row);
	while (row[x] == ' ')
		x++;
	if (row[x] != '1' || row[len - 1] != '1')
		return (0);
	return (1);
}

int	validate_row_spaces(char **map, int y, int x, t_game *game)
{
	int	row_len;
	int	prev_row_len;
	int	next_row_len;

	row_len = ft_strlen(map[y]);
	if (y < game->map.height - 1)
		next_row_len = ft_strlen(map[y + 1]);
	else
		next_row_len = 0;
	if (y != 0)
		prev_row_len = ft_strlen(map[y - 1]);
	else
		prev_row_len = 0;
	if (x > 0 && map[y][x - 1] != '1' && map[y][x - 1] != ' ')
		return (0);
	if (x + 1 < row_len && map[y][x + 1] != '1' && map[y][x + 1] != ' ')
		return (0);
	if (y > 0 && x < prev_row_len && map[y - 1][x] != '1' \
			&& map[y - 1][x] != ' ')
		return (0);
	if (y < game->map.height - 1 && x < next_row_len \
			&& map[y + 1][x] != '1' && map[y + 1][x] != ' ')
		return (0);
	return (1);
}

int	validate_top_and_bottom(char **map, t_game *game)
{
	int	x;

	x = 0;
	while (map[0][x] == ' ')
		x++;
	while (x < ft_strlen(map[0]))
	{
		while (map[0][x] == ' ')
			x++;
		if (map[0][x] != '1')
			return (0);
		x++;
	}
	x = 0;
	while (map[game->map.height - 1][x] == ' ')
		x++;
	while (x < ft_strlen(map[game->map.height - 1]))
	{
		while (map[game->map.height -1][x] == ' ')
			x++;
		if (map[game->map.height - 1][x] != '1')
			return (0);
		x++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	char	**map;
	int		y;
	int		x;
	int		row_len;

	map = game->map.points;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		row_len = ft_strlen(map[y]);
		if (!validate_row_edges(map[y], y))
			return (0);
		while (x < row_len)
		{
			if (map[y][x] == ' ' && !validate_row_spaces(map, y, x, game))
			{
				printf("No wall or spave next to space\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	if (!validate_top_and_bottom(map, game))
	{
		printf("Top or bottom row not fully wall\n");
		return (0);
	}
	return (1);
}
