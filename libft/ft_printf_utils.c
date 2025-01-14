/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:26:52 by ttero             #+#    #+#             */
/*   Updated: 2024/06/06 13:31:48 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr_mod(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		len = len + ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 10 && len >= 0)
	{
		len = len + ft_putnbr_mod(nb / 10);
		if (len >= 0)
			len = len + ft_putnbr_mod(nb % 10);
	}
	else if (len >= 0)
	{
		len = len + ft_putchar(nb + '0');
	}
	return (len);
}

int	ft_put_unsig(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb >= 10)
	{
		len = len + ft_put_unsig(nb / 10);
		if (len >= 0)
			len = len + ft_put_unsig(nb % 10);
	}
	else if (len >= 0)
	{
		len = len + ft_putchar(nb + '0');
	}
	return (len);
}

int	ft_putstr(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		if (write(1, &str[i], 1) < 0)
			return (-1);
		i++;
		j++;
	}
	return (j);
}
