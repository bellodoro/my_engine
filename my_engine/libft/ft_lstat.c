#include "libft.h"

t_list	*ft_lstat(t_list *list, size_t index)
{
	while (list && index)
	{
		list = list->next;
		--index;
	}
	return (list);
}
