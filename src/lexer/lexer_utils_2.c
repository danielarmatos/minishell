/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:14:44 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/19 20:21:18 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
