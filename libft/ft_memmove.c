/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:53:28 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 11:34:42 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (s < d)
	{
		s += n;
		d += n;
		while (n--)
			*--d = *--s;
		return (dest);
	}
	else
	{
		while (n--)
			*d++ = *s++;
		return (dest);
	}
	return (dest);
}
