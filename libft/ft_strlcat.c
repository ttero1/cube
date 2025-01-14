/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:31:41 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:15:44 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned long	i;
	unsigned long	j;
	size_t			x;
	int				flag;

	flag = 0;
	j = ft_strlen((char *)src);
	if (dst == 0 && size == 0)
		return (j);
	i = ft_strlen(dst);
	x = 0;
	if (size == 0)
		return (j);
	while (x < j && x + i < size - 1)
	{
		dst[i + x] = src[x];
		x++;
		flag = 1;
	}
	if (flag == 1)
		dst[i + x] = '\0';
	if (size < i)
		return (j + size);
	return (i + j);
}
