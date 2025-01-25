#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp_next;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		temp_next = (*lst)->next;
		(del)((*lst)->content);
		free(*lst);
		*lst = temp_next;
	}
	*lst = NULL;
}
