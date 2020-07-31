/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_reworked.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:27:10 by weilin            #+#    #+#             */
/*   Updated: 2020/07/31 15:30:32 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_strreset(char *s1, char *s2)
{
	if (s1 && !s2)
	{
		ft_strdel(&s1);
		return (NULL);
	}
	if (!s1 || !s2)
		return (NULL);
	ft_strdel(&s1);
	s1 = s2;
	return (s1);
}

static int	ft_return_line(char **s, char **line, const int fd, int rd)
{
	char		*n;
	int			len;
	int			slen;

	if (s[fd] && s[fd][0] != '\0' && (n = ft_strchr(s[fd], '\n')))
	{
		len = n - s[fd];
		slen = ft_strlen(s[fd]);
		*line = ft_strsub(s[fd], 0, len);
		s[fd] = ft_strreset(s[fd], ft_strsub(s[fd], len + 1, slen - len - 1));
		return (s[fd] != NULL ? 1 : -1);
	}
	else if (s[fd] && s[fd][0] != '\0')
	{
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
		if (ft_strlen(*line) == 0 && rd == 0)
		{
			*line = ft_strreset(*line, "\0");
			return (0);
		}
		return (1);
	}
	s[fd] ? ft_strdel(&s[fd]) : 0;
	return (0);
}

int			get_next_line2(const int fd, char **line, int rd)
{
	static char	*s[256];
	char		*buff;

	if (fd < 0 || !line || read(fd, NULL, 0) < 0 || BUFF_SIZE < 1 ||
		!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (s[fd] && ft_strlen(s[fd]) > 2048 && !ft_strchr(s[fd], '\n'))
		{
			ft_strdel(&buff);
			return (-1);
			break ;
		}
		buff[rd] = '\0';
		if (s[fd])
			s[fd] = ft_strreset(s[fd], ft_strjoin(s[fd], buff));
		else
			s[fd] = ft_strdup(buff);
		if (ft_strchr(buff, '\n'))
			break ;
		ft_strclr(buff);
	}
	ft_strdel(&buff);
	return (ft_return_line(s, line, fd, rd));
}
