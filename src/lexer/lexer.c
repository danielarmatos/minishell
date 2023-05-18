/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:00:11 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/18 10:29:21 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if (input[i + 1] == ' ' || input[i + 1] == '\"' || input[i + 1] == '\0')
				return (i + 1);
	j = i;
	if (quote < 2 || input[i] != '\"')
		while (input[j] && input[j] != 32 && input[j] != '\"' && !(input[j] >= 9 && input[j] <= 13) && input[j] != '|' && input[j] != '<' && input[j] != '>')
			j++;
	else
	{
		j++;
		i++;
		while (input[j] && input[j] != '\"')
			j++;
	}
	add_string_2(data, input, i, j);
	if (quote >= 2)
		j++;
	return (j - 1);
}

int add_token(t_data *data, char *input, int i)
{
	int	j;
	char *str;

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

void print_lexer(t_data *data)
{
	t_lexer	*node;

	node = data->lexer[0];
	while (node->next != NULL)
	{
		if (node->str != NULL)
			ft_printf("%i: %s\n", node->index, node->str);
		else
			ft_printf("\033[0;36m%i: %s\033[0m\n", node->index, node->token);
		node = node->next;
	}
	if (node->str != NULL)
		ft_printf("%i: %s\n", node->index, node->str);
	else
		ft_printf("\033[0;36m%i: %s\033[0m\n", node->index, node->token);
}

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
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i = add_token(data, input, i);
		else if (input[i] && (input[i] != '|' && input[i] != '<' && input[i] != '>'))
			i = add_string(data, input, i);
		i++;
	}
	//print_lexer(data);
	//parsing(data);
	return (1);
}
