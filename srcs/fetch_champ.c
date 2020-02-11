#include "asm.h"

char    *name_comment(char *line)
{
    int     i;
    int     j;
    int     len;
    char    *tmp;

    i = 0;
    j = 0;
    len = 0;
    while (line[i] != '"')
        i++;
    while (line[++i] != '"')
        len++;
    if (!(tmp = ft_strnew(len + 1)))
        return (NULL);
    i = 0;
    while (line[i] != '"')
        i++;
    while (line[++i] != '"')
        tmp[j++] = line[i];
    tmp[j] = '\0';
    return (tmp);
}

int     fetch_champ(t_env *env, char *line)
{
    t_champion  *champion;

    if (env->champion)
        champion = env->champion;
    else
    {
        if (!(champion = init_champion()))
            return (FAILURE);
        env->champion = champion;
    }
    if (!champion->name)
    {
        if (ft_strnstr(line, NAME_CMD_STRING, ft_strlen(line)) != 0)
            if (!(champion->name = name_comment(line)))
				return (FAILURE);
    }
    if (!champion->comment)
    {
        if (ft_strnstr(line, COMMENT_CMD_STRING, ft_strlen(line)) != 0)
            if (!(champion->comment = name_comment(line)))
				return (FAILURE);
    }
    return (SUCCESS);
}
