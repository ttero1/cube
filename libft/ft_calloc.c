/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:02:24 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:13:01 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void			*arr;
	size_t			total;

	if (nitems == 0 || size == 0)
		return (malloc(0));
	total = nitems * size;
	if (size != total / nitems)
		return (NULL);
	arr = malloc(total);
	if (!arr)
	{
		free(arr);
		return (arr);
	}
	ft_bzero(arr, total);
	return (arr);
}
