/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:00:25 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/09 21:04:00 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:36:52 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/09 18:32:39 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_quotes(char const *s)
{
	int count;
	int i;
	int check;

	count = 0;
	i = 0;
	while(s[i])
	{
		if (s[i] == 34)
			count++;
		i++;
	}
	check = count % 2;
	if (check == 0)
		return (-1);
	else
		return (count);
}

static int	ft_words(char const *s, char c, int quote_count)
{
	int	i;
	int	words;
	int quote;

	quote = 0;
	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while ((quote == 1 || s[i] != c) && s[i])
			{
				if (s[i] == 34)
				{
					if (quote == 0 && quote_count != 1)
						quote = 1;
					else
						quote = 0;
					quote_count--;
				}
				i++;
			}
		}
		else
			i++;
	}
	printf("words: %i\n", words);
	return (words);
}

static int	ft_word_size(char const *s, char c, int i, int quote_count)
{
	int	len;
	int quote;

	quote = 0;
	len = 0;
	while ((quote == 1 || s[i] != c) && s[i])
	{
		if (s[i] == 34)
		{
			if (quote == 0 && quote_count != 1)
				quote = 1;
			else
				quote = 0;
			quote_count--;
		}
		i++;
		len++;
	}
	return (len);
}

static char	*ft_word(char **arr, char *s, int i, char c, int quote_count)
{
	char	*word;
	int		wsize;

	wsize = ft_word_size(s, c, i, quote_count);
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

char	**input_split(char const *s, char c)
{
	int		words;
	int		i;
	int		j;
	char	**arr;
	int 	quote_count;

	if (!s)
		return (0);
	quote_count = check_quotes(s);
	words = ft_words(s, c, quote_count);
	arr = (char **) ft_calloc((words + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < words)
	{
		while (s[i] == c)
			i++;
		arr[j] = ft_word(arr + j, (char *)s, i, c, quote_count);
		i += ft_word_size(s, c, i, quote_count);
		quote_count--;
	}
	arr[j] = 0;
	return (arr);
}
/*

#include <stdio.h>

int	main(void)
{
//	char	s[] = "    Hello    wor  l d!  ";
	char	s[] = "split \"this for\" me \" ! lala\" ";
	char	**result;
	int		i = 0;

	result = ft_split(s, ' ');
	while (result[i])
	{
		puts(result[i]);
		i++;
	}
}*/
