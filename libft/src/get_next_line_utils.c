/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:22:35 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/11/25 11:10:19 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

void	*ft_memsetget(void *str, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)str;
	while (n-- > 0)
		*(p++) = (unsigned char)c;
	return (str);
}

void	*ft_callocget(size_t nmemb, size_t size)
{
	void	*str;

	str = (char *)malloc(size * nmemb);
	if (!str)
		return (NULL);
	return (ft_memsetget(str, 0, size * nmemb));
}

size_t	ft_strlenget(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchrget(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlenget(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoinget(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(((ft_strlenget(s1) + ft_strlenget(s2)) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlenget(s1) + ft_strlenget(s2)] = '\0';
	free(s1);
	s1 = 0;
	return (str);
}
