/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 10:34:40 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/24 10:38:36 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	ft_findnbr(const char *str, int base, char **endptr)
{
	int					small;
	unsigned long long	nb;

	small = 0;
	nb = 0;
	if (base <= 10)
		small = 10 - base;
	while (*str)
	{
		if (*str >= '0' && *str <= '9' - small)
			nb = (nb * base) + (*str++ - 48);
		else if (base > 10 && *str >= 'A' && *str <= ('Z' - (32 - base)))
			nb = (nb * base) + (*str++ - 55);
		else if (base > 10 && *str >= 'a' && *str <= ('z' - (32 - base)))
			nb = (nb * base) + (*str++ - 87);
		else
		{
			if (endptr != NULL)
				*endptr = (char *)str;
			return (nb);
		}
	}
	if (endptr != NULL)
		*endptr = (char *)str;
	return (nb);
}

long long			ft_strtoll(const char *str, char **endptr, int base)
{
	long long	nb;
	int			neg;
	int			i;

	if (str != NULL)
	{
		i = ft_skipspaces(str);
		neg = 0;
		if (str[0] == '-')
		{
			neg = 1;
			i++;
		}
		nb = ft_findnbr(&str[i], base, endptr);
		if (neg == 1)
			return (-nb);
		return (nb);
	}
	return (0);
}
