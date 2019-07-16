/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_strn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:29:55 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/15 15:41:03 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lst_to_strn(t_list *list, size_t size)
{
	t_list	*begin;
	char	*str;
	char	*src;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	begin = list;
	str = (char *)malloc(sizeof(char) * size);
	while (begin != NULL)
	{
		while (i < size)
		{
			src = (char *)begin->content;
			str[i] = src[j];
			i++;
			j++;
		}
		j = 0;
		begin = begin->next;
	}
	str[i] = '\0';
	return (str);
}
