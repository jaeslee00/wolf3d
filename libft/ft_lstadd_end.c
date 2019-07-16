/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:04:49 by viccarau          #+#    #+#             */
/*   Updated: 2018/12/02 15:07:55 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list	*curr;

	if (*alst)
	{
		curr = *alst;
		if (curr->next == NULL)
			curr->next = new;
		else
		{
			while (curr->next != NULL)
				curr = curr->next;
			if (curr->next == NULL)
				curr->next = new;
		}
	}
	else
		*alst = new;
}
