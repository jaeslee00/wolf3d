/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:52:35 by viccarau          #+#    #+#             */
/*   Updated: 2019/02/28 13:01:54 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newlst;

	newlst = (t_list *)malloc(sizeof(*newlst) * content_size);
	if (!newlst)
		return (NULL);
	if (!content)
	{
		newlst->content = NULL;
		newlst->content_size = 0;
	}
	else
	{
		newlst->content = malloc(sizeof(content) * content_size);
		if (!newlst->content)
			return (NULL);
		ft_memcpy(newlst->content, content, content_size);
		newlst->content_size = content_size;
	}
	newlst->next = NULL;
	return (newlst);
}
