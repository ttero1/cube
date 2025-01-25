#include "libft.h"

int	print_uint(unsigned int n, char *error_flag)
{
	unsigned int	count;

	count = 0;
	if (n >= 10)
	{
		count += print_uint(n / 10, error_flag);
		count += print_uint(n % 10, error_flag);
	}
	else
	{
		print_char(n + '0', error_flag);
		count++;
	}
	return (count);
}
