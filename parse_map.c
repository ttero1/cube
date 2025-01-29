/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:29:35 by mjaakkol          #+#    #+#             */
/*   Updated: 2025/01/29 10:56:24 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	save_line(char *line, t_game *game, int row)
{
	int	x;

	game->map.points[row] = ft_strdup(line);
	if (!game->map.points[row])
		return (0);
	x = 0;
	while (line[x])
	{
		if (ft_strchr("NSEW", line[x]))
		{
			if (game->player.x != -1)
				return (0);
			game->player.x = x;
			game->player.y = row;
			game->player.player_pos = line[x];
		}
		x++;
	}
	return (1);
}

int	process_content(char *line, t_game *game, int *row, int *map)
{
	while ((game->map.floor_color[0] == -1 || game->map.ceiling_color[0] == -1 \
				|| !game->map.no_text || !game->map.so_text || \
				!game->map.we_text || !game->map.ea_text) && *line == ' ')
		line++;
	if (game->map.floor_color[0] != -1 && game->map.ceiling_color[0] != -1 && \
			game->map.no_text && game->map.so_text && game->map.we_text \
			&& game->map.ea_text)
	{
		if (!check_valid_char(line))
			return (0);
	}
	if (!*map && parse_element(line, game) == -1)
		return (0);
	if (!*map && !parse_element(line, game))
	{
		if (!game->map.no_text || !game->map.so_text \
				|| !game->map.we_text || !game->map.ea_text)
			return (0);
		*map = 1;
		return (save_line(line, game, (*row)++));
	}
	else if (*map)
		return (save_line(line, game, (*row)++));
	return (1);
}

int	process_map(char *line, t_game *game, int fd, int *row)
{
	int	map;

	map = 0;
	while (line)
	{
		trim_newline(line);
		if (line[0] == '\0')
		{
			free(line);
			if (map)
				return (0);
			line = get_next_line(fd);
			continue ;
		}
		if (!process_content(line, game, row, &map))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!map)
		return (0);
	return (1);
}

int	finalize_map(t_game *game, int row)
{
	int	j;
	int	len;

	game->map.height = row;
	game->map.points[row] = NULL;
	game->map.width = 0;
	j = 0;
	len = 0;
	while (j < row)
	{
		len = ft_strlen(game->map.points[j]);
		if (len > game->map.width)
			game->map.width = len;
		j++;
	}
	if (!validate_map(game))
		return (0);
	if (!validate_player_position(game))
		return (0);
	return (1);
}

int	parse_map(const char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		row;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!init_map(file, game))
		return (0);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	row = 0;
	if (!process_map(line, game, fd, &row))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (finalize_map(game, row));
}
