#include "libft.h"

static size_t	ft_digit_count(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				count;
	int				temp;

	temp = n;
	count = ft_digit_count(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		temp = -temp;
		count++;
	}
	str = malloc((count + 1) * sizeof(char));
	if (!str)
		return (0);
	str[count] = '\0';
	while (count > 0)
	{
		str[--count] = temp % 10 + '0';
		temp = temp / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
