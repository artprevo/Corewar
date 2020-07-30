#include "asm.h"

int		not_allowed(char *line)
{
	int	i;
	int comment;

	comment = FALSE;
	i = 0;
	while (line[i])
	{
		if (line[i] == COMMENT_CHAR)
			comment = TRUE;
		if (strchr(LABEL_CHARS, line[i]) == 0 && line[i] != '\n' && line[i] != 9 &&
		strchr(ALLOWED_CHARS, line[i]) == 0)
		{
			if (comment == FALSE)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
