#include "libft.h"

int	print_int(int n, char *error_flag)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (print_str("-2147483648", error_flag));
	if (n < 0)
	{
		print_char('-', error_flag);
		n = -n;
		count++;
	}
	if (n >= 10)
	{
		count += print_int(n / 10, error_flag);
		count += print_int(n % 10, error_flag);
	}
	else
	{
		print_char(n + '0', error_flag);
		count++;
	}
	return (count);
}
