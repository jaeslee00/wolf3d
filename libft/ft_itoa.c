/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:51:50 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/23 19:45:09 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbofzero(int n, int *flag)
{
	unsigned int	nb;
	int				pow;

	pow = 1;
	nb = (unsigned int)n;
	if (n < 0)
	{
		nb = (unsigned int)-n;
		*flag = 2;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		pow++;
	}
	return (pow);
}

static void	ft_negative(char *str, int *n, unsigned int *nb, int *index)
{
	if (*n < 0)
	{
		str[0] = '-';
		*nb = (unsigned int)-*n;
		*index += 1;
	}
	else
		*nb = (unsigned int)*n;
	str[*index] = '\0';
}

char		*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	int				flag;
	int				i;

	if (n == 0)
		return (ft_strdup("0"));
	flag = 1;
	i = ft_nbofzero(n, &flag);
	str = (char *)malloc(sizeof(char) * (i + flag));
	if (str)
	{
		ft_negative(str, &n, &nb, &i);
		while (nb > 0)
		{
			str[--i] = (nb % 10) + '0';
			nb = nb / 10;
		}
		return (str);
	}
	else
		return (NULL);
}
