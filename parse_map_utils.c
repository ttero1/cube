/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.f>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:54:46 by mjaakkol          #+#    #+#             */
/*   Updated: 2025/01/29 10:54:54 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	search_char(char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return (1);
	else
		return (0);
}

int	check_valid_char(char *line)
{
	while (*line && *line != '\n')
	{
		if (!search_char("01NSEW ", *line))
			return (0);
		line++;
	}
	return (1);
}

void	trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	count_map_rows(const char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	while (line)
	{
		trim_newline(line);
		if (line[0] != '\0')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	init_map(const char *file, t_game *game)
{
	int	malloc_size;
	int	j;

	malloc_size = count_map_rows(file);
	if (malloc_size <= 0)
		return (0);
	game->map.points = malloc((malloc_size + 1) * sizeof(char *));
	if (!game->map.points)
		return (0);
	j = 0;
	while (j <= malloc_size)
	{
		game->map.points[j] = NULL;
		j++;
	}
	return (1);
}
