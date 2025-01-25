#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp_node;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp_node = *lst;
	while (temp_node->next)
		temp_node = temp_node->next;
	temp_node->next = new;
}
