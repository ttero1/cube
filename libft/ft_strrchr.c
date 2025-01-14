/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:43:33 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:16:10 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	x;

	x = c;
	i = ft_strlen((char *)s) - 1;
	if (x == 0)
		return ((char *)s + i + 1);
	while (i > 0)
	{
		if (s[i] == x)
		{
			return ((char *)s + i);
		}
		i--;
	}
	if (s[i] == x)
		return ((char *)s + i);
	return (0);
}
