/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:24:36 by ttero             #+#    #+#             */
/*   Updated: 2023/11/09 12:13:45 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	struct s_list	*last;
	int				i;
	struct s_list	*t;

	i = 1;
	if (lst == NULL)
		return ;
	last = *lst;
	while (last)
	{
		t = last->next;
		ft_lstdelone(last, del);
		last = t;
		i++;
	}
	*lst = NULL;
}
