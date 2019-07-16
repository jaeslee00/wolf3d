/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:53:11 by viccarau          #+#    #+#             */
/*   Updated: 2019/03/12 15:24:50 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*a;
	unsigned char		*b;

	a = (const unsigned char *)src;
	b = (unsigned char *)dst;
	while (n--)
		*b++ = *a++;
	return (dst);
}
