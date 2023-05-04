/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:36:52 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/01 20:02:40 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	ft_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (words);
}

static int	ft_word_size(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		i++;
		len++;
	}
	return (len);
}

static char	*ft_word(char **arr, char *s, int i, char c)
{
	char	*word;
	int		wsize;

	wsize = ft_word_size(s, c, i);
	word = ft_substr(s, i, wsize);
	if (!arr)
	{
		while (*arr--)
			free(*arr--);
		free(arr);
		return (NULL);
	}
	return (word);
}

char	**prompt_split(char const *s, char c)
{
	int		words;
	int		i;
	int		j;
	char	**arr;

	if (!s)
		return (0);
	words = ft_words(s, c);
	arr = (char **) malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < words)
	{
		while (s[i] == c)
			i++;
		arr[j] = ft_word(arr + j, (char *)s, i, c);
		i += ft_word_size(s, c, i);
	}
	arr[j] = 0;
	return (arr);
}
