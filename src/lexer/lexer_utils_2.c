/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:14:44 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/14 19:50:15 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_odd_quotes(int quote_count, char quote_type)
{
	if ((quote_count % 2) != 0)
	{
		ft_printf("minishell: unexpected EOF while looking for matching `%c'\n",
			quote_type);
		exit_status = 2;
		return (0);
	}
	else
		return (1);
}

char	*count_quotes(t_data *data, char *str)
{
	int		j;
	int		quote_count;
	char	quote_type;

	quote_count = 0;
	quote_type = 'n';
	j = -1;
	while (str[++j])
	{
		if (quote_type == 'n' && (str[j] == '\'' || str[j] == '\"'))
		{
			quote_type = str[j++];
			quote_count++;
		}
		if (quote_type != 'n' && str[j] == quote_type)
		{
			quote_type = 'n';
			quote_count++;
		}
		if (str[j] == '$' && quote_type != '\'')
			str = expander(data, str, j);
	}
	if (check_odd_quotes(quote_count, quote_type) == 0)
		return (0);
	return (str);
}

int	validate_tokens(t_data *data)
{
	int		len;
	int		i;
	t_lexer	*node;

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
				exit_status = 2;
				return (0);
			}
		}
		node = node->next;
		i++;
	}
	return (1);
}

int	check_lexer(t_data *data)
{
	if (data->lexer[0])
	{
		if (!data->lexer[0]->next)
		{
			if (data->lexer[0]->token)
			{
				ft_printf("minishell: syntax error near unexpected "
					"token `%c'\n", data->lexer[0]->token[0]);
				exit_status = 2;
				return (0);
			}
		}
		if (validate_tokens(data) == 0)
			return (0);
		parsing(data);
		return (1);
	}
	else
		return (0);
}
