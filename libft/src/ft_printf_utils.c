/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 09:58:59 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/12/01 09:59:02 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putstrf(char *str)
{
	if (!str)
		return (ft_putstrf("(null)"));
	return (write(1, str, ft_strlen(str)));
}

int	ft_putcharf(char c)
{
	int	sayi;

	sayi = 0;
	sayi += write(1, &c, 1);
	return (sayi);
}

int	ft_putnbrf(int number)
{
	char	*num;
	int		len;

	len = 0;
	num = ft_itoa(number);
	len += ft_putstrf(num);
	free(num);
	return (len);
}

int	ft_putunint(unsigned int number)
{
	int	i;

	i = 0;
	if (number > 9)
		i += ft_putunint(number / 10);
	write(1, &"0123456789"[number % 10], 1);
	i++;
	return (i);
}
