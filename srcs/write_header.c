#include "asm.h"

static int		write_prog_name(t_champion *champ)
{
	char	*name;
	int		i;

	if (!(name = ft_memalloc(ft_strlen(champ->name))))
		return (FAILURE);
	i = -1;
	while ((champ->name)[++i])
		name[i] = (champ->name)[i];
	write(champ->fd, name, ft_strlen(champ->name));
	free(name);
	return (SUCCESS);
}

static int		write_comment(t_champion *champ)
{
	char	*comment;
	int		i;

	if (!(comment = ft_memalloc(ft_strlen(champ->comment))))
		return (FAILURE);
	i = -1;
	while ((champ->comment)[++i])
		comment[i] = (champ->comment)[i];
	lseek(champ->fd, 0x8c, SEEK_SET);
	write(champ->fd, comment, ft_strlen(champ->comment));
	free(comment);
	return (SUCCESS);
}

static int		write_prog_size(t_env *env, t_champion *champ)
{
	char	*prog_size;

	if (!(prog_size = ft_memalloc(4)))
		return (FAILURE);
	env->prog_size = 1235;
	printf("0xff = %d\n", 0xff);
	prog_size[3] = env->prog_size + 0xff;
	printf("prog_size[3] = %3d, prog = %3d\n", prog_size[3], env->prog_size);
	prog_size[2] = (env->prog_size >> 8) + 0xff;
	printf("prog_size[2] = %3d, prog >> 8 = %3d\n", prog_size[2],( env->prog_size >> 8));
	prog_size[1] = (env->prog_size >> 16) + 0xff;
	printf("prog_size[1] = %3d, prog >> 16 = %3d\n", prog_size[1],( env->prog_size >> 16));
	prog_size[0] = (env->prog_size >> 24) + 0xff;
	printf("prog_size[0] = %3d, prog >> 24 = %3d\n", prog_size[0],( env->prog_size >> 24));
	lseek(champ->fd, 0x88, SEEK_SET);
	write(champ->fd, prog_size, 4);
	free(prog_size);
	return (SUCCESS);
}

int				write_header(t_env *env)
{
	t_champion	*champ;
	int			*magic;
	char		c;

	champ = env->champion;
	if (!(magic = ft_memalloc(sizeof(int))))
		return (FAILURE);
	magic[0] = COREWAR_EXEC_MAGIC;
	write(champ->fd, magic, 4);
	if (write_prog_name(champ) == FAILURE)
		return (FAILURE);
	if (write_comment(champ) == FAILURE)
		return (FAILURE);
	if (write_prog_size(env, champ) == FAILURE)
		return (FAILURE);
	lseek(champ->fd, 0x88F, SEEK_SET);
	c = 0x0;
	write(champ->fd, &c, 1);
	free(magic);
	return (SUCCESS);
}
