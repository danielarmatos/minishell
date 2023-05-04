/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 09:58:23 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/12/01 09:58:37 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char	*ft_convert(size_t num, char *set)
{
	static char	buffer[50];
	char		*ptr;
	int			base;

	base = ft_strlen(set);
	ptr = &buffer[49];
	*ptr = '\0';
	*--ptr = set[num % base];
	num /= base;
	while (num != 0)
	{
		*--ptr = set[num % base];
		num /= base;
	}
	return (ptr);
}

int	ft_sign(char c, va_list macro)
{
	if (c == 'c')
		return (ft_putcharf(va_arg(macro, int)));
	else if (c == 's')
		return (ft_putstrf(va_arg(macro, char *)));
	else if (c == 'p')
		return (ft_putpoint(va_arg(macro, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbrf(va_arg(macro, int)));
	else if (c == 'u')
		return (ft_putunint(va_arg(macro, unsigned int)));
	else if (c == '%')
		return (ft_putcharf('%'));
	else if (c == 'x')
		return (ft_putstrf(\
		ft_convert(va_arg(macro, unsigned int), "0123456789abcdef")));
	else if (c == 'X')
		return (ft_putstrf(\
		ft_convert(va_arg(macro, unsigned int), "0123456789ABCDEF")));
	return (0);
}

int	ft_printf(const char *sign, ...)
{
	va_list	macro;
	int		i;
	int		len;

	va_start(macro, sign);
	i = 0;
	len = 0;
	while (sign[i])
	{
		if (sign[i] == '%')
		{
			len += ft_sign(sign[i + 1], macro);
			i++;
		}
		else
			len += write(1, &sign[i], 1);
		i++;
	}
	va_end(macro);
	return (len);
}
