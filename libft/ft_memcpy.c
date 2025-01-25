#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*to;
	const char	*from;
	size_t		i;
	size_t		j;

	to = (char *)dst;
	from = (const char *)src;
	if (!to && !from)
		return (0);
	i = 0;
	j = 0;
	while (i < n)
	{
		to[j] = from[i];
		j++;
		i++;
	}
	return ((char *)dst);
}
