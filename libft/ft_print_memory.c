/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 14:26:23 by viccarau          #+#    #+#             */
/*   Updated: 2019/04/29 14:13:31 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_memory(unsigned char c)
{
	char	*hex;

	hex = "0123456789abcdef";
	ft_putchar(hex[c / 16]);
	ft_putchar(hex[c % 16]);
}

static void	ft_add_mem(unsigned char *mem, unsigned int size, unsigned int i)
{
	unsigned int	j;

	ft_put_addr(mem);
	ft_putstr(":  ");
	j = 0;
	while (j < 16)
	{
		if (i * 16 + j < size)
			ft_put_memory(mem[j]);
		else
			ft_putstr("  ");
		if (j && (j + 1) % 2 == 0)
			ft_putchar(' ');
		j++;
	}
}

void		*ft_print_memory(const void *addr, size_t size)
{
	unsigned char	*mem;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	mem = (unsigned char *)addr;
	while (i * 16 < size)
	{
		ft_add_mem(mem, size, i);
		j = 0;
		while (j < 16)
		{
			if (ft_isprint(mem[j]) && i * 16 + j < size)
				ft_putchar(mem[j]);
			else if (i * 16 + j < size)
				ft_putchar('.');
			j++;
		}
		ft_putchar('\n');
		mem += 16;
		i++;
	}
	return ((void *)addr);
}
