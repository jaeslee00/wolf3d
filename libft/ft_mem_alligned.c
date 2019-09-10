/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:00:03 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/28 14:42:26 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

unsigned char	is_power_of_two(long long unsigned int x)
{
	return ((x & (x-1)) == 0);
}

long long unsigned int align_forward(long long unsigned int ptr,
	size_t align)
{
	long long unsigned int	p;
	long long unsigned int	a;
	long long unsigned int	modulo;

	p = ptr;
	a = (long long unsigned int)align;
	modulo = p & (a-1);
	if (modulo != 0)
		return (a - modulo);
	return (0);
}

void			*ft_mem(t_mem *mem, size_t size)
{
	void *p;
	int	offset;
	int	align;

	align = 2 * sizeof(void *);
	offset = align_forward((long long unsigned int)mem->m, align);
	size += offset;
	if (mem->tsize < (size + mem->usize))
		return (NULL);
	ft_memset(mem->m + mem->usize, 0, size);
	p = mem->m + mem->usize + offset;
	mem->usize = mem->usize + size + offset;
	return (p);
}
