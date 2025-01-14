/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:57:23 by ttero             #+#    #+#             */
/*   Updated: 2023/11/24 12:04:08 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	void	*content;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new = NULL;
	temp = 0;
	while (lst)
	{
		content = f(lst->content);
		temp = ft_lstnew(content);
		if (!(temp))
		{
			free(content);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}
