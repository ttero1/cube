#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*to;
	const char	*from;
	size_t		i;

	to = (char *)dst;
	from = (const char *)src;
	if (!to && !from)
		return (0);
	i = 0;
	if (to < from && len != 0)
	{
		while (++i <= len)
		{
			to[i - 1] = from [i - 1];
		}
	}
	else
	{
		while (len-- > 0)
		{
			to[len] = from[len];
		}
	}
	return ((char *)dst);
}
