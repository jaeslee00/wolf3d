/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:02:02 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 11:31:40 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		j = i;
		k = 0;
		while (str[j] == to_find[k] && j < len)
		{
			j++;
			k++;
			if (to_find[k] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
