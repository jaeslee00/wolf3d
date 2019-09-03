/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_addr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:29:29 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/22 21:42:25 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_addr(void *mem)
{
	unsigned long long	nb;
	unsigned char	addr[13];
	char			*hex;
	int				i;

	nb = (unsigned long long)mem;
	hex = "0123456789abcdef";
	i = 0;
	while (i < 12)
	{
		addr[i] = hex[nb % 16];
		nb /= 16;
		i++;
	}
	i--;
	ft_putstr("0x");
	while (i >= 0)
	{
		ft_putchar(addr[i]);
		i--;
	}
}
