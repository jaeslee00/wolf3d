/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:51:59 by viccarau          #+#    #+#             */
/*   Updated: 2019/02/28 13:13:01 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (*alst)
		new->next = *alst;
	*alst = new;
}

void	ft_lstradd(t_list **alst, t_list *new)
{
	t_list	*iter;

	if (*alst)
	{
		iter = *alst;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new;
	}
}
