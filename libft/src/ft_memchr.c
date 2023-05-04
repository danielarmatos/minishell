/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:47:49 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/11/04 14:22:05 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;
	int				i;

	str = (unsigned char *)s;
	ch = c;
	i = 0;
	while (n--)
	{
		if (*str++ == ch)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
