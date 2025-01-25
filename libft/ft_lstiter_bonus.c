#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp_next;

	if (!lst || !f)
		return ;
	while (lst)
	{
		temp_next = lst->next;
		(f)(lst->content);
		lst = temp_next;
	}
}
