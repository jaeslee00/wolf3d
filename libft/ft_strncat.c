/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:01:39 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/23 19:39:02 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*str1;

	str1 = s1;
	while (*str1)
		str1++;
	while (*s2 && n-- > 0)
		*str1++ = *s2++;
	*str1 = '\0';
	return (s1);
}