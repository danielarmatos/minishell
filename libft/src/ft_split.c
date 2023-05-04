/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:40:48 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/11/11 11:53:11 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	count(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] != c && s[i])
			i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	ini;
	size_t	fim;
	size_t	i;

	if (!s)
		return (0);
	str = (char **)ft_calloc((count(s, c) + 1), sizeof(char *));
	if (!str)
		return (0);
	ini = 0;
	fim = 0;
	i = 0;
	while (i < count(s, c))
	{
		while (s[ini] == c)
			ini++;
		fim = ini;
		while (s[fim] != c && s[fim])
			fim++;
		str[i++] = ft_substr(s, ini, (fim - ini));
		ini = fim;
	}
	return (str);
}
