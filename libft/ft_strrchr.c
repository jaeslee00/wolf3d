/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:02:06 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/26 22:17:20 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	char		*temp;

	i = 0;
	temp = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			temp = ((char *)&s[i]);
		i++;
	}
	if (c == '\0' && s[i] == '\0')
		temp = ((char *)&s[i]);
	return (temp);
}
