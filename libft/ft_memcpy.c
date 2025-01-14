/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:53:43 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:14:42 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned long	i;
	char			*s1;
	char			*s2;

	s1 = (char *)dest;
	s2 = (char *)src;
	if (s1 == 0 && s2 == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dest);
}
