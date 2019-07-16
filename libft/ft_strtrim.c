/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:02:23 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 11:17:18 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_trim(char **start, char **end)
{
	char	*str;
	int		i;

	str = *start;
	i = 0;
	while (ft_iswhitespace(str[i]) && str[i + 1] != '\0')
	{
		*start = &str[i];
		i++;
	}
	*start = &str[i];
	*end = &str[i];
	while (str[i] != '\0')
	{
		if (!ft_iswhitespace(str[i]))
			*end = &str[i];
		i++;
	}
}

char		*ft_strtrim(char const *s)
{
	char	*start;
	char	*end;
	char	*str;
	size_t	len;

	if (s)
	{
		start = (char *)s;
		end = (char *)s;
		ft_trim(&start, &end);
		if (ft_iswhitespace(start[0]) && ft_iswhitespace(end[0]))
			str = ft_strdup("");
		else
		{
			len = (end - start) + 2;
			str = (char *)malloc(sizeof(char) * len);
			if (str)
				ft_strlcpy(str, start, len);
		}
		if (str)
			return (str);
		return (NULL);
	}
	return (NULL);
}
