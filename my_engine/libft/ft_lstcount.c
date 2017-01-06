#include "libft.h"

int		ft_lstcount(t_list *lst)
{
	int		i;

	i = 0;
	while (lst && lst->next)
	{
		lst = lst->next;
		++i;
	}
	return (i + 1);
}
