#include "asm.h"

int		label_name(char *line, t_param *param, int i)
{
	int		len;
	int		j;
	char	*tmp;

	len = 0;
	j = 0;
	if (!(line[i]))
		return (FAILURE);
	while (line[i] && strchr(LABEL_CHARS, line[i]) != 0)
	{
		len++;
		i++;
	}
	if (!(tmp = ft_strnew(len + 1)))
		return (FAILURE);
	i = i - len;
	while (line[i] && strchr(LABEL_CHARS, line[i]) != 0)
		tmp[j++] = line[i++];
	tmp[j] = '\0';
	param->label = tmp;
	printf("param->label = %s\n", tmp);
	return (SUCCESS);
}
