/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:14:44 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/22 21:10:52 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int validate_tokens(t_data *data)
{
	int	len;
	int	i;
	t_lexer *node;

	node = data->lexer[0];
	i = 0;
	len = get_lexer_len(data->lexer[0]);
	while (i < len)
	{
		if (node->token)
		{
			if (!node->next)
			{
				ft_printf("minishell: syntax error\n");
				return (0);
			}
		}
		node = node->next;
		i++;
	}
	return (1);
}

int check_lexer(t_data *data)
{
	if (data->lexer[0])
	{

		if (!data->lexer[0]->next)
			if (data->lexer[0]->token)
			{
				ft_printf("minishell: syntax error near unexpected "
						  "token `%c'\n", data->lexer[0]->token[0]);
				return (0);
			}
		if (validate_tokens(data) == 0)
			return (0);
		expander(data, data->lexer[0]);
		//print_lexer(data);
		parsing(data);
		return (1);
	}
	else
		return (0);
}

int	single_quote(char *input, int i)
{
	int	quote;

	quote = 1;
	i++;
	while (input[i])
	{
		if (input[i] == '\'')
			quote++;
		i++;
	}
	return (quote);
}

int	double_quote(char *input, int i)
{
	int	quote;

	quote = 1;
	i++;
	while (input[i])
	{
		if (input[i] == '\"')
			quote++;
		i++;
	}
	return (quote);
}

int	check_quote(char *input, int i)
{
	int	quote;

	quote = 0;
	if (input[i] == '\"')
		quote = double_quote(input, i);
	else if (input[i] == '\'')
		quote = single_quote(input, i);
	if (quote % 2 != 0)
		quote--;
	return (quote);
}
