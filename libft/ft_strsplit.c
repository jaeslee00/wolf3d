/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:02:10 by viccarau          #+#    #+#             */
/*   Updated: 2018/11/09 12:02:42 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_copy_word(char *dest, const char *src,
									int place, int size)
{
	int	i;

	i = 0;
	place -= size - 1;
	while (size > 0)
	{
		dest[i] = src[place];
		i++;
		size--;
		place++;
	}
	dest[i] = '\0';
	return (dest);
}

static unsigned	int	ft_word_size(const char *str, int place, int c)
{
	int	i;

	i = 0;
	while (place >= 0)
	{
		if (str[place] == c)
			break ;
		place--;
		i++;
	}
	return (i);
}

static unsigned	int	ft_count_words(const char *str, int c)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			x++;
		i++;
	}
	x++;
	return (x);
}

static char			**ft_taballoc(char **tab, const char *str, char c)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	tab = (char **)malloc(sizeof(char *) * ft_count_words(str, c) + 1);
	if (tab != NULL)
		while (str[i] != '\0')
		{
			if ((str[i + 1] == c) || str[i + 1] == '\0')
			{
				if ((size = ft_word_size(str, i, c)) > 0)
				{
					tab[j] = (char *)malloc(sizeof(char) * size + 1);
					tab[j] = ft_copy_word(tab[j], str, i, size);
					j++;
				}
			}
			i++;
		}
	if (tab != NULL)
		tab[j] = NULL;
	return (tab);
}

char				**ft_strsplit(const char *str, char c)
{
	char	**tab;

	tab = NULL;
	if (str != NULL)
		tab = ft_taballoc(tab, str, c);
	return (tab);
}
