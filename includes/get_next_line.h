/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 07:14:34 by viccarau          #+#    #+#             */
/*   Updated: 2019/04/29 14:12:32 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# define BUFF_SIZE (4096)

typedef struct	s_gnl
{
	char	*tmp;
	char	*buf;
	ssize_t	size;
}				t_gnl;

int				get_next_line(int const fd, char **line);
#endif
