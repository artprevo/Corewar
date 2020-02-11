#include "asm.h"

int     fetch_actions(t_env *env, char *line)
{
	if (env->champion_fetched == TRUE)
	{
		if (fetch_label(env, line) == FAILURE)
			return (FAILURE);
		if (fetch_op(env, line) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
