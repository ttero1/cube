/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:38:54 by ttero             #+#    #+#             */
/*   Updated: 2023/11/23 12:43:05 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocate_mem(char const *s, size_t len, unsigned int start)
{
	char	*sub;
	size_t	x;

	x = len + 1;
	if (ft_strlen(s + start) < len)
	{
		sub = (char *)malloc(ft_strlen(s + start) + 1);
		if (!sub)
		{
			free(sub);
			return (NULL);
		}
	}
	else
	{
		sub = (char *)malloc(x);
		if (!sub)
		{
			free(sub);
			return (NULL);
		}
	}
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned long	j;
	char			*sub;

	if (start >= ft_strlen(s))
	{
		sub = malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	i = start;
	j = 0;
	sub = allocate_mem(s, len, start);
	if (!sub)
		return (NULL);
	while (s[i] && j < len)
	{
		sub[j] = s[i];
		i++;
		j++;
	}
	sub[j] = '\0';
	return (sub);
}
