/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:00:11 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/11 21:00:11 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote(char *input, int i)
{
	int	quote;

	quote = 0;
	if (input[i] == '\"')
	{
		quote = 1;
		i++;
		while (input[i])
		{
			if (input[i] == '\"')
				quote++;
			i++;
		}
	}
	if (quote % 2 != 0)
		quote--;
	return (quote);
}

int	add_string_2(t_data *data, char *input, int i, int j)
{
	char	*str;
	int		x;

	(void)data;
	x = 0;
	str = ft_calloc(((j - i) + 1), sizeof(char));
	if (!str)
		return (0);
	while (x < (j - i))
	{
		str[x] = input[i + x];
		x++;
	}
	add_node(data->lexer, create_str_node(str));
	return (1);
}

int	add_string(t_data *data, char *input, int i)
{
	int		quote;
	int		j;

	quote = check_quote(input, i);
	if (input[i] == '\"')
		if (quote < 2)
			i++;
	j = i;
	if (quote < 2)
		while (input[j] && input[j] != 32 && !(input[j] >= 9 && input[j] <= 13))
			j++;
	else
	{
		j++;
		i++;
		while (input[j] && input[j] != '\"')
			j++;
	}
	add_string_2(data, input, i, j);
	return (j);
}

/*int add_token(t_data *data, char *input, int i)
{

	return (0);
}*/

int	lexical_analysis(t_data *data)
{
	t_lexer	**lexer;
	int		i;
	char	*input;

	input = data->prompt;
	i = 0;
	lexer = malloc(sizeof(t_lexer *));
	if (!lexer)
		return (0);
	(*lexer) = 0;
	data->lexer = lexer;
	while (input[i])
	{
		while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
			i++;
		//if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			//add_token(data, input, i);
		if (input[i] != '|' && input[i] != '<' && input[i] != '>')
			i = add_string(data, input, i);
		i++;
	}
	//ft_printf("\nlexer: %s \n", data->lexer[0]->str);
	return (1);
}
