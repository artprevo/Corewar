#include "libft.h"

void    free_buff(t_buff *buff)
{
	t_buff *tmp;

	while (buff)
	{
		tmp = buff->next;
		if (buff->buff);
			free(buff->buff);
		free(buff);
		buff = tmp;
	}
}