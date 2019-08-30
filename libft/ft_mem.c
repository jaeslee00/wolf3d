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

void			*ft_mem(t_mem *mem, size_t size)
{
	void *p;

	if (mem->tsize < (size + mem->usize))
	return (NULL);
	p = mem->m + mem->usize;
	mem->usize = mem->usize + size;
	return (p);
}
