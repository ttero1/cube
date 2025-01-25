#include "get_next_line.h"

static char	*update_remainder(char *remainder)
{
	size_t	i;
	size_t	j;
	char	*new_remainder;

	i = 0;
	if (!remainder)
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	if (!remainder[i])
		return (free_buffer(&remainder));
	new_remainder = malloc(((str_len(remainder) - i) + 1) * sizeof(char));
	if (!new_remainder)
		return (free_buffer(&remainder));
	j = 0;
	while (remainder[i])
		new_remainder[j++] = remainder[i++];
	new_remainder[j] = '\0';
	free(remainder);
	return (new_remainder);
}

static char	*get_newline(char *remainder)
{
	size_t	i;
	char	*new_line;

	i = 0;
	if (!remainder[i] || !remainder)
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	new_line = malloc((i + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		new_line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

static char	*read_buffer(int fd, char *buffer, char *remainder)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = remainder;
		remainder = str_join(temp, buffer);
		if (!remainder)
		{
			free(temp);
			return (NULL);
		}
		free(temp);
		temp = NULL;
		if (check_newline_char(buffer) == 1)
			break ;
	}
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_buffer(&remainder));
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_buffer(&remainder));
	remainder = read_buffer(fd, buffer, remainder);
	free(buffer);
	buffer = NULL;
	if (!remainder)
		return (NULL);
	line = get_newline(remainder);
	if (!line)
		return (free_buffer(&remainder));
	remainder = update_remainder(remainder);
	return (line);
}
