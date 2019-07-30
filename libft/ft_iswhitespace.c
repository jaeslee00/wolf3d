/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:51:41 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 11:35:37 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iswhitespace(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\n')
	|| (c == '\v') || (c == '\f') || (c == '\r'))
		return (1);
	else
		return (0);
}