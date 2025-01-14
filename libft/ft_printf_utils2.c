/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:30:16 by ttero             #+#    #+#             */
/*   Updated: 2024/06/06 13:31:48 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len = len + ft_putchar(nb + '0');
	else if (nb >= 16 && len >= 0)
	{
		len = len + ft_puthex(nb / 16);
		if (len >= 0)
			len = len + ft_puthex(nb % 16);
	}
	else if (len >= 0)
	{
		if (nb <= 9)
			len = len + ft_putchar(nb + '0');
		else
			len = len + ft_putchar(nb - 10 + 'a');
	}
	return (len);
}

int	ft_puthex_cap(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len = len + ft_putchar(nb + '0');
	else if (nb >= 16 && len >= 0)
	{
		len = len + ft_puthex_cap(nb / 16);
		if (len >= 0)
			len = len + ft_puthex_cap(nb % 16);
	}
	else if (len >= 0)
	{
		if (nb <= 9)
			len = len + ft_putchar(nb + '0');
		else
			len = len + ft_putchar(nb - 10 + 'A');
	}
	return (len);
}

int	ft_puthex_long(unsigned long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len = len + ft_putchar(nb + '0');
	else if (nb >= 16 && len >= 0)
	{
		len = len + ft_puthex_long(nb / 16);
		if (len >= 0)
			len = len + ft_puthex_long(nb % 16);
	}
	else if (len >= 0)
	{
		if (nb <= 9)
			len = len + ft_putchar(nb + '0');
		else
			len = len + ft_putchar(nb - 10 + 'a');
	}
	return (len);
}

int	convert(void *pointer)
{
	uintptr_t	a;
	int			i;

	if (write(1, "0x", 2) <= 0)
		return (-1);
	i = 2;
	a = (uintptr_t)pointer;
	i = i + ft_puthex_long(a);
	return (i);
}
