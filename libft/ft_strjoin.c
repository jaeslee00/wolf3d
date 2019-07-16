/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:00:58 by viccarau          #+#    #+#             */
/*   Updated: 2018/12/02 15:08:26 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;

	if (s1 && s2)
	{
		i = 0;
		str = (char *)ft_memalloc(sizeof(char) *
				((ft_strlen((char *)s1) + 1) + ft_strlen((char *)s2) + 1));
		if (str)
		{
			ft_strcpy(str, s1);
			while (s1[i] != '\0')
				i++;
			ft_strcpy(&str[i], s2);
			return (str);
		}
		return (NULL);
	}
	return (NULL);
}
