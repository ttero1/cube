#include "libft.h"

static size_t	ft_str_len(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*new_string;

	if (!s1 || !s2)
		return (0);
	new_string = malloc((ft_str_len(s1) + ft_str_len(s2) + 1) * sizeof(char));
	if (!new_string)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new_string[i + j] = s2[j];
		j++;
	}
	new_string[i + j] = '\0';
	return (new_string);
}
