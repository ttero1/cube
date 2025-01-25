#include "libft.h"

int	print_str(char *s, char *error_flag)
{
	int	i;

	i = 0;
	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
		{
			*error_flag = 1;
			return (-1);
		}
		return (6);
	}
	while (s[i] != '\0')
		i++;
	if (write(1, s, i) == -1)
	{
		*error_flag = 1;
		return (-1);
	}
	return (i);
}
