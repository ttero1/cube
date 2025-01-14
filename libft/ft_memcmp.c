/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:35:53 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:14:35 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned long	i;
	unsigned char	*x;
	unsigned char	*z;

	i = 0;
	x = (unsigned char *)str1;
	z = (unsigned char *)str2;
	while (i < n)
	{
		if (x[i] != z[i])
		{
			return (x[i] - z[i]);
		}
		i++;
	}
	return (0);
}
