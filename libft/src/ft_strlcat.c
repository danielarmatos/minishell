/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:35:28 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/11/03 15:07:48 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	int		i;
	int		j;
	size_t	len;

	if (dest)
		len = ft_strlen(dest);
	else
		len = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size > 0 && size > len)
	{
		i = len;
		j = 0;
		while (src[j] && i < (int)size - 1)
		{
			dest[i] = src[j];
			j++;
			i++;
		}
		dest[i] = '\0';
		return (len + ft_strlen(src));
	}
	return (size + ft_strlen(src));
}
