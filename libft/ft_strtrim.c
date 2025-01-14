/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:00:27 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:16:25 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	forward(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (set[j] && s1[i])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = -1;
		}
		j++;
	}
	return (i);
}

static int	backward(char const *s1, char const *set)
{
	int		j;
	int		z;

	j = 0;
	z = ft_strlen((char *)s1) - 1;
	while (set[j] && z >= 0)
	{
		if (s1[z] == set[j])
		{
			z--;
			j = -1;
		}
		j++;
	}
	return (z);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		z;
	char	*arr;

	if (ft_strlen(set) == 0)
	{
		arr = ft_strdup((char *)s1);
		return (arr);
	}
	z = ft_strlen((char *)s1) - 1;
	i = forward (s1, set);
	z = backward(s1, set);
	if (z <= 0)
	{
		arr = malloc(1);
		if (!arr)
			return (NULL);
		arr[0] = '\0';
		return (arr);
	}
	arr = ft_substr(s1, i, z - i + 1);
	return (arr);
}
