/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:27:21 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/11/09 11:48:39 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	size;

	if (!s1 || !set)
		return (NULL);
	size = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (size > i && ft_strchr(set, s1[size]))
		size--;
	str = ft_substr((char *)s1, i, (size - i) + 1);
	if (!str)
		return (NULL);
	return (str);
}
