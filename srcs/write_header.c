/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:13:21 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 14:04:33 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		write_prog_size(t_env *env, t_champion *champ)
{
	char	*prog_size;

	if (env->prog_size > CHAMP_MAX_SIZE)
		ft_error5("Champion's code is too long, it may not work on VM\n");
	if (env->prog_size == 0)
		ft_error5("Champion's code is empty, but here goes his identity\n");
	if (!(prog_size = ft_memalloc(4)))
		ft_error2("Error on prog_size malloc\n");
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
		ft_error2("Error on magic malloc");
	magic[0] = 0xf383ea00;
	write(champ->fd, magic, 4);
	if (ft_strlen(champ->name) > PROG_NAME_LENGTH)
		ft_error2("Champion's name is too long\n");
	if (ft_strlen(champ->comment) > COMMENT_LENGTH)
		ft_error2("Champion's comment is too long\n");
	if (champ->name)
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
