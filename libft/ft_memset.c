#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dest;
	unsigned int	i;

	dest = b;
	i = 0;
	while (i < len)
	{
		dest[i] = c;
		i++;
	}
	return ((unsigned char *)b);
}
