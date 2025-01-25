#include "libft.h"

int	print_hex(unsigned int n, const char *format, char *error_flag)
{
	const char	*base;
	int			nibbles;

	nibbles = 0;
	if (*format == 'x')
		base = "0123456789abcdef";
	if (*format == 'X')
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		nibbles += print_hex(n / 16, format, error_flag);
		nibbles += print_hex(n % 16, format, error_flag);
	}
	else
	{
		print_char(base[n], error_flag);
		nibbles++;
	}
	return (nibbles);
}
