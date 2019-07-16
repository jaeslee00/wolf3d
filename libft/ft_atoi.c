/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:50:42 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/23 22:00:54 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	value;
	int	negative;

	i = ft_skipspaces(str);
	value = 0;
	negative = 0;
	if (str[i] == '-')
		negative = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] < 48 || str[i] > 57)
		return (0);
	while (str[i] >= 48 && str[i] <= 57)
	{
		value *= 10;
		value += str[i] - '0';
		i++;
	}
	if (negative == 1)
		return (-value);
	else
		return (value);
}
