#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned char	*str;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return ((char *)str);
}
