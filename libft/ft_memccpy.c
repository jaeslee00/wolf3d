/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:52:55 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 11:35:07 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	i = 0;
	a = (unsigned char*)src;
	b = (unsigned char*)dst;
	while (i < n)
	{
		b[i] = a[i];
		if (a[i] == ((unsigned char)c))
			return (&b[i + 1]);
		i++;
	}
	return (NULL);
}
