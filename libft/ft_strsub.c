/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:02:18 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 11:17:41 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			j;

	if (s)
	{
		j = 0;
		i = start;
		str = (char *)malloc(len + 1);
		if (str)
		{
			while (j < len)
			{
				str[j] = s[i];
				i++;
				j++;
			}
			str[j] = '\0';
			return (str);
		}
		else
			return (NULL);
	}
	return (NULL);
}
