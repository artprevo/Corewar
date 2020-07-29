#include "asm.h"

static void		write_prog_size(t_env *env, t_champion *champ)
{
	char	*prog_size;

	if (!(prog_size = ft_memalloc(4)))
		ft_error(champ->env, "Error on malloc");
	prog_size[3] = env->prog_size & 0xff;
	prog_size[2] = (env->prog_size >> 8) & 0xff;
	prog_size[1] = (env->prog_size >> 16) & 0xff;
	prog_size[0] = (env->prog_size >> 24) & 0xff;
	lseek(champ->fd, 0x88, SEEK_SET);
	write(champ->fd, prog_size, 4);
	free(prog_size);
}

void			write_header(t_env *env)
{
	t_champion	*champ;
	int			*magic;
	char		c;

	champ = env->champion;
	if (!(magic = ft_memalloc(sizeof(int))))
		ft_error(env, "Error on malloc");
	magic[0] = 0xf383ea00;
	write(champ->fd, magic, 4);
	if (champ)
		write(champ->fd, champ->name, ft_strlen(champ->name));
	if (champ->comment)
	{
		lseek(champ->fd, 0x8c, SEEK_SET);
		write(champ->fd, champ->comment, ft_strlen(champ->comment));
	}
	write_prog_size(env, champ);
	lseek(champ->fd, 0x88F, SEEK_SET);
	c = 0x0;
	write(champ->fd, &c, 1);
	free(magic);
}
