/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:01:23 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 11:32:36 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		i;

	i = 0;
	if (s)
	{
		str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
		if (str)
		{
			while (s[i] != '\0')
			{
				str[i] = f(s[i]);
				i++;
			}
			str[i] = '\0';
			return (str);
		}
		else
			return (NULL);
	}
	else
		return (NULL);
}
