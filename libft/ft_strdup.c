#include "libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned int		c;
	char				*dest;
	char				*src;

	c = 0;
	src = (char *)s1;
	while (src[c] != '\0')
		c++;
	dest = malloc((c + 1) * sizeof(char));
	if (!dest)
		return (0);
	c = 0;
	while (src[c] != '\0')
	{
		dest[c] = src[c];
		c++;
	}
	dest[c] = '\0';
	return (dest);
}
