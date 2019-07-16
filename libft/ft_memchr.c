/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:53:02 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 11:34:52 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*f;
	size_t			i;

	f = (unsigned char *)s;
	i = 0;
	if (n)
	{
		while (i < n)
		{
			if (f[i] == ((unsigned char)c))
				return (&f[i]);
			i++;
		}
	}
	return (NULL);
}
