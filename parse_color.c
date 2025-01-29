/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:43:09 by mjaakkol          #+#    #+#             */
/*   Updated: 2025/01/29 15:12:09 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

int	parse_color(char *line, int *color)
{
	char	**rgb;

	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		if (rgb)
			free_rgb(rgb);
		return (0);
	}
	color[0] = ft_atoi(rgb[0]);
	color[1] = ft_atoi(rgb[1]);
	color[2] = ft_atoi(rgb[2]);
	free_rgb(rgb);
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 \
		|| color[1] > 255 || color[2] < 0 || color[2] > 255)
		return (0);
	return (1);
}

int	floor_color(char *line, t_game *game)
{
	if (game->map.floor_color[0] != -1)
		return (-1);
	if (!parse_color(line + 2, game->map.floor_color))
		return (-1);
	return (1);
}

int	ceiling_color(char *line, t_game *game)
{
	if (game->map.ceiling_color[0] != -1)
		return (-1);
	if (!parse_color(line + 2, game->map.ceiling_color))
		return (-1);
	return (1);
}
