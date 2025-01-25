#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*c;
	unsigned int		i;
	unsigned int		j;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	if (start > i)
		return (ft_strdup(""));
	if (len > (i - start))
		len = (i - start);
	c = malloc((len + 1) * sizeof(char));
	if (!c)
		return (0);
	j = 0;
	while (j < len && s[start + j] != '\0')
	{
		c[j] = s[start + j];
		j++;
	}
	c[j] = '\0';
	return (c);
}
