/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:45:34 by ttero             #+#    #+#             */
/*   Updated: 2023/11/23 12:29:46 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_power(int nb, int power)
{
	int			original;
	int			i;
	long int	x;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	x = nb;
	original = x;
	i = 1;
	while (i < power)
	{
		x = x * original;
		i++;
	}
	return (x);
}

static char	*mem(int n, int len, char *res)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	if (n == 0)
	{
		res[0] = '0';
		i++;
	}
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
		i++;
	}
	while (len > 0)
	{
		z = n % (ft_power(10, len)) / (ft_power(10, len - 1));
		res[i] = z + '0';
		i++;
		len--;
	}
	res[i] = '\0';
	return (res);
}

static int	lenght(int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	if (n == -2147483648)
	{
		res = ft_strdup("-2147483648");
		if (!res)
			return (NULL);
		return (res);
	}
	len = lenght(n);
	if (n <= 0)
	{
		res = (char *)malloc(len + 2);
	}
	else
		res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	res = mem(n, len, res);
	return (res);
}
