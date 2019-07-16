/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:00:03 by viccarau          #+#    #+#             */
/*   Updated: 2019/04/29 16:31:14 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void			*ft_mem(t_mem *mem, size_t size)
{
	void *p;

	if (mem->tsize < (size + mem->usize))
	{
		if ((p = ft_memalloc((2 * mem->tsize) + size + mem->usize)) == NULL)
			return (NULL);
		mem->tsize = ((2 * mem->tsize) + size + mem->usize);
		if (mem->m != NULL)
		{
			ft_memcpy(p, mem->m, mem->usize);
			free(mem->m);
		}
		mem->m = p;
	}
	p = mem->m + mem->usize;
	mem->usize = mem->usize + size;
	return (p);
}
