/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:58:28 by ttero             #+#    #+#             */
/*   Updated: 2024/07/04 16:09:03 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_get_decimal(char *str, double *decimal)
{
	double	factor;

	factor = 1;
	if (*str == '.')
		str++;
	while (*str)
	{
		*decimal = *decimal * 10 + (*str - '0');
		factor *= 10;
		str++;
	}
	*decimal /= factor;
}

double	ft_atod(char *str)
{
	double	res;
	double	decimal;
	int		flag;

	res = 0;
	decimal = 0;
	flag = 1;
	if (*str == '-')
	{
		flag = -1;
		str++;
	}
	while (*str && *str != '.')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	ft_get_decimal(str, &decimal);
	return (flag * (res + decimal));
}
