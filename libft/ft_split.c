/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:58:55 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:15:16 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_array(char **split, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	len_word(char *str, char charset, int i)
{
	int	j;

	j = 0;
	i++;
	while (str[i] && str[i] != charset)
	{
		i++;
		j++;
	}
	j++;
	return (j);
}

static int	word(char *str, char charset)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != charset)
		{
			k++;
			i++;
		}
		if ((str[i] != charset) && ((str[i - 1] == charset) || i == 0))
		{
			k++;
		}
		i++;
	}
	return (k);
}

static int	loop(char *str, char charset, char **split, int k)
{
	int	i;
	int	z;
	int	j;

	i = 0;
	z = 0;
	j = 0;
	while (z < k)
	{
		while (str[i] == charset)
			i++;
		j = len_word(str, charset, i);
		split[z] = malloc(j + 1);
		if (!(split[z]))
		{
			free_array(split, z);
			return (0);
		}
		ft_strlcpy(split[z], str + i, j + 1);
		i = i + j;
		z++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		k;

	i = 0;
	k = 0;
	split = malloc((word((char *)s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	if (word((char *)s, c) == 0)
	{
		split[0] = NULL;
		return (split);
	}
	if (!(split))
		return (NULL);
	i = loop((char *)s, c, split, word((char *)s, c));
	if (i == 0)
		return (NULL);
	k = word((char *)s, c);
	split[k] = 0;
	return (split);
}
