/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:02:14 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 11:18:56 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		j = i;
		k = 0;
		while (str[j] == to_find[k])
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
