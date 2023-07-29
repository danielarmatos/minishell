/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:00:11 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/29 19:55:06 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *input, t_data *data, char quote_type)
{
	int		j;
	int		k;

	data->exporting = 0;
	j = (ft_strlen(input) - 1);
	while (j >= 0)
	{
		if (quote_type == 'n' && (input[j] == '\'' || input[j] == '\"'))
		{
			quote_type = input[j];
			ft_strlcpy(&input[j], &input[j + 1], ft_strlen(input));
			k = j;
			j++;
		}
		if (quote_type != 'n' && input[j] == quote_type)
		{
			quote_type = 'n';
			ft_strlcpy(&input[j], &input[j + 1], ft_strlen(input));
			if (k == j + 1)
				data->exporting = 1;
		}
		j--;
	}
	return (input);
}

int	add_string_2(t_data *data, char *input, int i, int j)
{
	char	*str;
	char	*str2;
	int		x;

	x = 0;
	str = ft_calloc(((j - i) + 1), sizeof(char));
	if (!str)
		return (0);
	while (x < (j - i))
	{
		str[x] = input[i + x];
		x++;
	}
	str2 = count_quotes(data, str, 'n');
	if (str2 == 0)
	{
		if (str)
			free(str);
		return (-1);
	}
	str2 = remove_quotes(str2, data, 'n');
	add_node(data->lexer, create_str_node(str2));
	return (1);
}

int	add_string(t_data *data, char *input, int i, char quote_type)
{
	int		j;

	j = i;
	while (input[j])
	{
		if (quote_type == 'n' && (input[j] == '\'' || input[j] == '\"'))
			if (input[j + 1] != '\0')
				quote_type = input[j++];
		if (quote_type == 'n' && (input[j] == ' ' || input[j] == '|'
				|| input[j] == '<' || input[j] == '>'))
			break ;
		if (quote_type != 'n' && input[j] == quote_type
			&& (input[j + 1] == ' ' || input[j + 1] == '\0'))
		{
			j++;
			break ;
		}
		if (quote_type != 'n' && input[j] == quote_type)
			quote_type = 'n';
		j++;
	}
	if (add_string_2(data, input, i, j) == -1)
		return (-1);
	return (j - 1);
}

int	add_token(t_data *data, char *input, int i)
{
	int		j;
	char	*str;

	j = i;
	if (input[i] == '|')
		str = "|";
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		str = "<<";
		j++;
	}
	else if (input[i] == '>' && input[i + 1] == '>')
	{
		str = ">>";
		j++;
	}
	else if (input[i] == '<')
		str = "<";
	else if (input[i] == '>')
		str = ">";
	else
		return (j);
	add_node(data->lexer, create_token_node(str));
	return (j);
}

int	lexical_analysis(t_data *data, char *input)
{
	t_lexer	**lexer;
	int		i;

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
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i = add_token(data, input, i);
		else if (input[i] && (input[i] != '|' && input[i] != '<'
				&& input[i] != '>'))
			i = add_string(data, input, i, 'n');
		if (i == -1)
			return (0);
		i++;
		if (i > ((int) ft_strlen(input)))
			break ;
	}
	return (check_lexer(data));
}
