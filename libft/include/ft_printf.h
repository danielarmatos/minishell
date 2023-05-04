/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 09:58:45 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/12/01 09:58:51 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  FT_PRINTF_H

# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"
# include <stdlib.h>

int		ft_putstrf(char *str);
int		ft_printf(const char *sign, ...);
int		ft_putcharf(char c);
int		ft_putpoint(void *ptr);
int		ft_putnbrf(int number);
int		ft_putunint(unsigned int number);
char	*ft_convert(size_t num, char *set);

#endif
