/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:07:47 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/11/11 15:26:12 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	countnum(int n)
{
	int	num;

	num = 0;
	if (n == 0)
		num = 1;
	if (n < 0)
	{
		n *= -1;
		num++;
	}
	while (n)
	{
		n /= 10;
		num++;
	}
	return (num);
}

static char	*convert(int num, int n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (num + 1));
	if (!str)
		return (NULL);
	str[i] = '0';
	if (n < 0)
	{
		str[i++] = '-';
		if (n == -2147483648)
		{
			str[1] = '2';
			n = -147483648;
		}
		n *= -1;
	}
	i = num - 1;
	while (n > 0)
	{
		str[i--] = ((n % 10) + 48);
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;

	count = countnum(n);
	str = convert(count, n);
	str[count] = 0;
	return (str);
}
