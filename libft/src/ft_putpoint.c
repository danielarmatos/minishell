/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:11:00 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/12/01 11:19:49 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	ft_pointbase(void *ptr)
{
	unsigned long	ret;
	int				res;

	ret = (unsigned long)ptr;
	res = 0;
	if (ret > 15)
		res += ft_pointbase((void *)(ret / 16));
	res += ft_putcharf("0123456789abcdef"[ret % 16]);
	return (res);
}

int	ft_putpoint(void *ptr)
{
	int				res;

	if (ptr == 0)
		return (ft_putstrf("(nil)"));
	ft_putstrf("0x");
	res = ft_pointbase(ptr);
	return (res + 2);
}
