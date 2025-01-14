/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:31:26 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:15:30 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*arr;
	int		i;
	int		j;

	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	arr = (char *)malloc(len1 + len2 + 1);
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len1)
	{
		arr[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		arr[i + j] = s2[j];
		j++;
	}
	arr[i + j] = '\0';
	return (arr);
}
