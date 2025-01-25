#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*dest;
	size_t	i;

	dest = (char *)s;
	i = 0;
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
}
