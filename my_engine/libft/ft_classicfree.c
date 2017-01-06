#include "libft.h"

void					ft_classicfree(void *content, size_t size)
{
	(void)size;
	free(content);
}
