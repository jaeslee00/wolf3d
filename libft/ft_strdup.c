/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:00:36 by viccarau          #+#    #+#             */
/*   Updated: 2018/12/26 12:59:05 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char *dup;

	dup = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (dup)
	{
		ft_strcpy(dup, str);
		return (dup);
	}
	else
		return (NULL);
}
