#include "libft.h"

int	print_char(char c, char *error_flag)
{
	if (*error_flag)
		return (-1);
	if (write(1, &c, 1) == -1)
	{
		*error_flag = 1;
		return (-1);
	}
	return (1);
}
