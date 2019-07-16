/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 10:26:03 by viccarau          #+#    #+#             */
/*   Updated: 2019/04/29 16:33:09 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_line(char **line, t_mem *mem)
{
	char	*str;
	char	*tmp;

	str = (char *)(mem->m + (BUFF_SIZE + 1));
	if (((tmp = ft_memchr(str, '\n', (mem->usize - (BUFF_SIZE + 1)))) != NULL))
	{
		tmp[0] = '\0';
		if (!(*line = ft_strnew((tmp + 2 - str))))
			return (-1);
		*line = ft_memcpy(*line, str, ((tmp + 1) - str));
		str = ft_memcpy(str, tmp + 1, ((mem->usize) - BUFF_SIZE));
		mem->usize -= (tmp + 1) - str;
		return (1);
	}
	return (0);
}

static int		ft_init(t_mem *mem, t_gnl *gnl)
{
	if (mem->m == NULL)
	{
		if (((mem->m = ft_memalloc((42 * 1024) + BUFF_SIZE)) == NULL))
			return (-1);
		mem->tsize = ((42 * 1024) + BUFF_SIZE);
		if ((ft_mem(mem, (BUFF_SIZE + 1))) == NULL)
			return (-1);
	}
	gnl->buf = (char *)mem->m;
	return (0);
}

static int		ft_last_line(char **line, t_mem *mem)
{
	char	*str;

	str = (char *)(mem->m + (BUFF_SIZE + 1));
	if (str[0] != '\0')
	{
		if ((*line = ft_strdup(str)) == NULL)
			return (-1);
		ft_memdel(&mem->m);
		mem->m = NULL;
		return (1);
	}
	return (0);
}

static int		return_handle(t_mem *mem, int error, int fd)
{
	if (error > 0)
		return (1);
	else if (fd < 0 || fd > 10)
		return (-1);
	else
	{
		ft_memdel(&mem->m);
		mem->tsize = 0;
		mem->usize = 0;
		return (error);
	}
}

int				get_next_line(const int fd, char **line)
{
	int				ret;
	char			temp;
	t_gnl			gnl;
	static t_mem	mem[10];

	ret = -1;
	if (line == NULL || BUFF_SIZE <= 0 || ((read(fd, &temp, 0)) == -1)
		|| ((ft_init(&mem[fd], &gnl)) == -1) ||
		(ret = ft_line(line, &mem[fd])) != 0)
		return (return_handle(&mem[fd], ret, fd));
	while ((gnl.size = read(fd, gnl.buf, BUFF_SIZE)) > 0)
	{
		gnl.buf[gnl.size] = '\0';
		if ((gnl.tmp = ft_mem(&mem[fd], gnl.size)) == NULL)
			return (-1);
		gnl.buf = (char *)mem[fd].m;
		ft_memcpy(gnl.tmp, gnl.buf, gnl.size);
		if ((ret = ft_line(line, &mem[fd])) != 0)
			return (return_handle(&mem[fd], ret, fd));
	}
	if (gnl.size != -1 && (ret = ft_last_line(line, &mem[fd])))
		return (return_handle(&mem[fd], ret, fd));
	return (return_handle(&mem[fd], gnl.size, fd));
}
