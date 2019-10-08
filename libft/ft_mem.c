/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:00:03 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/08 16:53:02 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_mem(t_mem *mem, size_t size)
{
	void *p;

	if (mem->tsize < (size + mem->usize))
		return (NULL);
	p = mem->m + mem->usize;
	mem->usize = mem->usize + size;
	return (p);
}
