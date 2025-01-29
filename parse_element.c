/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:45:24 by mjaakkol          #+#    #+#             */
/*   Updated: 2025/01/29 10:45:53 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	no_text(char *line, t_game *game)
{
	char	*trimmed;

	if (game->map.no_text)
		return (-1);
	trimmed = ft_strtrim(line + 3, " ");
	if (!check_png_file(trimmed))
	{
		free(trimmed);
		return (0);
	}
	game->map.no_text = ft_strdup(trimmed);
	free(trimmed);
	if (!game->map.no_text)
		return (-1);
	return (1);
}

int	so_text(char *line, t_game *game)
{
	char	*trimmed;

	if (game->map.so_text)
		return (-1);
	trimmed = ft_strtrim(line + 3, " ");
	if (!check_png_file(trimmed))
	{
		free(trimmed);
		return (0);
	}
	game->map.so_text = ft_strdup(trimmed);
	free(trimmed);
	if (!game->map.so_text)
		return (-1);
	return (1);
}

int	we_text(char *line, t_game *game)
{
	char	*trimmed;

	if (game->map.we_text)
		return (-1);
	trimmed = ft_strtrim(line + 3, " ");
	if (!check_png_file(trimmed))
	{
		free(trimmed);
		return (0);
	}
	game->map.we_text = ft_strdup(trimmed);
	free(trimmed);
	if (!game->map.we_text)
		return (-1);
	return (1);
}

int	ea_text(char *line, t_game *game)
{
	char	*trimmed;

	if (game->map.ea_text)
		return (-1);
	trimmed = ft_strtrim(line + 3, " ");
	if (!check_png_file(trimmed))
	{
		free(trimmed);
		return (0);
	}
	game->map.ea_text = ft_strdup(trimmed);
	free(trimmed);
	if (!game->map.ea_text)
		return (-1);
	return (1);
}

int	parse_element(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (no_text(line, game));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (so_text(line, game));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (we_text(line, game));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (ea_text(line, game));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (floor_color(line, game));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (ceiling_color(line, game));
	return (0);
}
