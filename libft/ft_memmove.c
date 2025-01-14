/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:00:25 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:14:49 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	unsigned long	i;
	char			*x;
	char			*z;

	x = (char *)str1;
	z = (char *)str2;
	i = 0;
	if (str1 < str2)
	{
		while (i < n)
		{
			x[i] = z[i];
			i++;
		}
	}
	if (str1 > str2)
	{
		i = n;
		while (i > 0)
		{
			x[i - 1] = z[i - 1];
			i--;
		}
	}
	return (x);
}
