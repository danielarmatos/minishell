/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:00:11 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/19 21:33:50 by dreis-ma         ###   ########.fr       */
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
	char	quote_type;
	int		j;

	if (input[i] == '\"')
	{
		quote_type = 'd';
		if (input[i + 1] == '\"' || input[i + 1] == '\0')
			return (i + 1);
	}
	else if (input[i] == '\'')
	{
		quote_type = 's';
		if (input[i + 1] == '\'' || input[i + 1] == '\0')
			return (i + 1);
	}
	quote = check_quote(input, i);
	j = i;
	if (quote < 2 || (input[i] != '\"' && input[i] != '\''))
		while (input[j] && input[j] != 32
			&& !(input[j] >= 9 && input[j] <= 13) && input[j] != '|'
			&& input[j] != '<' && input[j] != '>')
				j++;
	else
	{
		j++;
		i++;
		if (quote_type == 's')
			while (input[j] && input[j] != '\'')
				j++;
		else
		{
			while (input[j] && input[j] != '\"')
				j++;
			//input = d_quotes_expander(data, input, i, j);
			if (d_quotes_expander(data, input, i, j) != NULL)
			{
				input = d_quotes_expander(data, input, i, j);
				//ft_printf("HERE:\n%s\n%i\n%i\n", input, i, ft_strlen(input));
				add_string_2(data, input, i, ft_strlen(input));
			}
			else
				add_string_2(data, input, i, j);
			if (quote >= 2)
				j++;
			return (j - 1);
		}
	}
	add_string_2(data, input, i, j);
	if (quote >= 2)
		j++;
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

void	print_lexer(t_data *data)
{
	t_lexer	*node;

	if (!data->lexer[0])
		return ;
	node = data->lexer[0];
	while (node->next != NULL)
	{
		if (node->str != NULL)
			ft_printf("%i: %s\n", node->index, node->str);
		else if (node->token != NULL)
			ft_printf("\033[0;36m%i: %s\033[0m\n", node->index, node->token);
		node = node->next;
	}
	if (node->str != NULL)
		ft_printf("%i: %s\n", node->index, node->str);
	else if (node->token != NULL)
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
		else if (input[i] && (input[i] != '|' && input[i] != '<'
				&& input[i] != '>'))
			i = add_string(data, input, i);
		i++;
	}
	//print_lexer(data);
	if (data->lexer[0])
		parsing(data);
	return (1);
}
