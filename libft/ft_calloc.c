#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char		*p;
	size_t				i;

	if (count && size && (SIZE_MAX / size) < count)
		return (0);
	p = malloc(count * size);
	if (!p)
		return (0);
	i = 0;
	while (i < (count * size))
	{
		p[i] = 0;
		i++;
	}
	return (p);
}
