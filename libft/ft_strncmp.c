/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:01:44 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 11:32:14 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1[i] != '\0' || s2[i] != '\0')
	{
		while (i < n)
		{
			if (s1[i] == '\0' && s2[i] == '\0')
				return (0);
			if (s1[i] != s2[i])
				return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
			i++;
		}
	}
	return (0);
}
