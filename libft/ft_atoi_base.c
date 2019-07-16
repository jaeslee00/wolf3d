/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 18:55:29 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/24 10:14:26 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_findnbr(const char *str, int base)
{
	int	small;
	int	nb;

	small = 0;
	nb = 0;
	if (base <= 10)
		small = 10 - base;
	while (*str)
	{
		if (*str >= '0' && *str <= '9' - small)
			nb = (nb * base) + (*str++ - 48);
		else if (base > 10 && *str >= 'A' && *str <= ('F' - (16 - base)))
			nb = (nb * base) + (*str++ - 55);
		else if (base > 10 && *str >= 'a' && *str <= ('f' - (16 - base)))
			nb = (nb * base) + (*str++ - 87);
		else
			return (nb);
	}
	return (nb);
}

int			ft_atoi_base(const char *str, int str_base)
{
	int		nb;
	int		neg;
	int		i;

	if (str != NULL)
	{
		i = ft_skipspaces(str);
		neg = 0;
		if (str[0] == '-')
		{
			neg = 1;
			i++;
		}
		nb = ft_findnbr(&str[i], str_base);
		if (neg == 1)
			return (-nb);
		return (nb);
	}
	return (0);
}
