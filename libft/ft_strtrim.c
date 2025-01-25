#include "libft.h"

static	int	ft_is_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == (unsigned char)c)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_start(char const *s1, char const *set)
{
	unsigned int	start;

	start = 0;
	while (s1[start] != '\0' && ft_is_set(s1[start], set))
		start++;
	return (start);
}

static int	ft_end(char const *s1, char const *set)
{
	unsigned int	end;
	unsigned int	start;

	end = 0;
	start = ft_start(s1, set);
	while (s1[end] != '\0')
		end++;
	while ((end > start) && ft_is_set(s1[end - 1], set))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	len;
	unsigned int	i;
	char			*new_string;
	unsigned int	start;
	unsigned int	end;

	if (!set || !s1)
		return (0);
	start = ft_start(s1, set);
	end = ft_end(s1, set);
	len = end - start;
	new_string = malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (0);
	i = 0;
	while (len > i)
	{
		new_string[i] = s1[start + i];
		i++;
	}
	new_string[len] = '\0';
	return (new_string);
}
