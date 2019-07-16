/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:09:39 by viccarau          #+#    #+#             */
/*   Updated: 2018/12/02 15:09:35 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lst_to_str(t_list *list)
{
	char	*str;
	t_list	*begin;
	int		i;
	int		j;

	i = 0;
	begin = list;
	while (begin != NULL)
	{
		i += begin->content_size;
		begin = begin->next;
	}
	i++;
	str = (char *)ft_memalloc(sizeof(char) * i);
	begin = list;
	j = 0;
	while (begin != NULL)
	{
		if (begin->content_size)
			ft_strcpy(&str[j], (char *)begin->content);
		j += begin->content_size;
		begin = begin->next;
	}
	str[j] = '\0';
	return (str);
}
