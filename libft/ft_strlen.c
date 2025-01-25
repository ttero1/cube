#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
	{
		l++;
	}
	return (l);
}
