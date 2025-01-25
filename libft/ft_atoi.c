#include "libft.h"

int	ft_atoi(const char *str)
{
	long long int	res;
	long long int	temp;
	int				s;

	res = 0;
	s = 1;
	while (*str && (*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			s = -s;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		temp = res;
		res = res * 10 + s * (*str - '0');
		if (temp > res && s > 0)
			return (-1);
		if (temp < res && s < 0)
			return (0);
		str++;
	}
	return (res);
}
