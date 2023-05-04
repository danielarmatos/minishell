/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:22:48 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/11/03 13:34:13 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*temp;
	char	*d;

	temp = (char *)src;
	d = (char *)dest;
	if (temp < d)
	{
		while (n--)
			d[n] = temp[n];
	}
	else
		ft_memcpy(d, temp, n);
	return (dest);
}
