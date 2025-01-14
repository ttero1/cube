/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:11:43 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:16:03 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned long	i;
	int				j;
	int				leng;

	j = 0;
	i = 0;
	if (little[i] == 0)
		return ((char *)big);
	if (len == 0)
		return (0);
	leng = ft_strlen((char *)little);
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
			j++;
		else
		{
			i -= j;
			j = 0;
		}
		if (j == leng)
			return ((char *)big + i - j + 1);
		i++;
	}
	return (0);
}
