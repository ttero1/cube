#include "libft.h"

static void	print_ptr_rec(unsigned long n, const char *base, char *error_flag)
{
	if (n >= 16)
	{
		print_ptr_rec(n / 16, base, error_flag);
		print_ptr_rec(n % 16, base, error_flag);
	}
	else
		print_char(base[n], error_flag);
}

int	print_ptr(unsigned long n, char *error_flag)
{
	const char		*base;
	int				i;
	unsigned long	temp;

	i = 2;
	base = "0123456789abcdef";
	print_str("0x", error_flag);
	if (n == 0)
	{
		print_char('0', error_flag);
		i++;
	}
	else
	{
		temp = n;
		while (temp > 0)
		{
			i++;
			temp = temp / 16;
		}
		print_ptr_rec(n, base, error_flag);
	}
	return (i);
}
