#include "get_next_line.h"

size_t	str_len(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

char	*str_join(char *remainder, char *buffer)
{
	int		i;
	int		j;
	char	*new_string;
	size_t	rem_len;

	rem_len = 0;
	if (remainder)
		rem_len = str_len(remainder);
	new_string = malloc(((rem_len + str_len(buffer)) + 1) * sizeof(char));
	if (!new_string || (!remainder && !buffer))
		return (NULL);
	i = 0;
	j = 0;
	while (remainder && remainder[i] != '\0')
	{
		new_string[i] = remainder[i];
		i++;
	}
	while (buffer && buffer[j] != '\0')
	{
		new_string[i + j] = buffer[j];
		j++;
	}
	new_string [i + j] = '\0';
	return (new_string);
}

char	check_newline_char(char *remainder)
{
	size_t	i;

	i = 0;
	while (remainder[i])
	{
		if (remainder[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*free_buffer(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}
