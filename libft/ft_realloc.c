/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:30:28 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 11:34:07 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *mem, size_t size)
{
	void			*reloc;

	reloc = ft_memalloc(size);
	if (mem != NULL)
	{
		if (reloc != NULL)
		{
			ft_memmove(reloc, mem, size);
			ft_memdel(&mem);
		}
	}
	else
		reloc = ft_memalloc(size);
	return (reloc);
}
