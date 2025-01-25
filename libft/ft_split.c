#include "libft.h"

static char	**ft_free(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	return (NULL);
}

static size_t	ft_count(char const *s, char c)
{
	int			len;
	size_t		count;
	int			i;
	const char	*str;

	len = ft_strlen(s);
	i = 0;
	count = 0;
	str = (const char *)s;
	while (i < len)
	{
		while (i < len && str[i] == c)
			i++;
		if (i < len && str[i] != c)
			count++;
		while (i < len && str[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_copy(char const *s, int start, int end)
{
	const char	*str;
	char		*dest;
	int			i;

	str = (const char *)s;
	dest = malloc((end - start + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (start < end)
	{
		dest[i] = str[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**ft_new_array(char **new_array, char const *s, char c)
{
	size_t		i;
	size_t		j;
	size_t		start;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != '\0' && s[i] != c)
				i++;
			new_array[j] = ft_copy(s, start, i);
			if (!new_array[j])
			{
				return (ft_free(new_array));
			}
			j++;
		}
		else
			i++;
	}
	new_array[j] = NULL;
	return (new_array);
}

char	**ft_split(char const *s, char c)
{
	char		**new_array;
	size_t		count;

	if (!s)
		return (0);
	count = ft_count(s, c);
	new_array = malloc((count + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	new_array = ft_new_array(new_array, s, c);
	return (new_array);
}
