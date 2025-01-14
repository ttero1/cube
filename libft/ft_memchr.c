/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:33:09 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:14:28 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned long	i;
	char			*x;
	char			z;

	i = 0;
	z = c;
	x = (char *)str;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (x[i] == z)
		{
			return ((void *)str + i);
		}
		i++;
	}
	return (NULL);
}
