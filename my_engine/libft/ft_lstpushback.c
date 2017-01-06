#include "libft.h"

void					ft_lstpushback(t_list **alst, t_list *new)
{
	t_list	*iter;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	iter = *alst;
	while (iter->next)
		iter = iter->next;
	iter->next = new;
}
