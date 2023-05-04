/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:55:47 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/11/09 10:52:52 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*out;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		out = ft_calloc(1, 1);
		if (!out)
			return (NULL);
		return (out);
	}
	i = 0;
	out = (char *)malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	while (i < len)
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
