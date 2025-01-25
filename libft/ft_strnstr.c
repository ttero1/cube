#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	c;
	unsigned int	i;
	char			*h;
	char			*n;

	h = (char *)haystack;
	n = (char *)needle;
	if (*needle == 0 || !needle)
		return (h);
	c = 0;
	while (h[c] != '\0' && c < len)
	{
		i = 0;
		while (h[c + i] != '\0' && h[c + i] == n[i] && (c + i) < len)
		{
			i++;
		}
		if (n[i] == '\0')
			return (h + c);
		c++;
	}
	return (0);
}
