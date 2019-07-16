/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:01:10 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/23 20:00:37 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	srclen;
	size_t	newlen;

	if (src != NULL && dest != NULL)
	{
		srclen = (size_t)ft_strlen((char *)src);
		if (n == 0)
			return (srclen);
		if (srclen >= n)
			newlen = n - 1;
		else
			newlen = srclen;
		ft_strncpy(dest, src, newlen);
		dest[newlen] = '\0';
		return (srclen);
	}
	return (0);
}
