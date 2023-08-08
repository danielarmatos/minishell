/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:14:44 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/04 20:44:30 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_odd_quotes(int quote_count, char quote_type)
{
	if ((quote_count % 2) != 0)
	{
		ft_printf("minishell: unexpected EOF while looking for matching `%c'\n",
			quote_type);
		g_exit_status = 2;
		return (0);
	}
	else
		return (1);
}

char	*count_quotes(t_data *data, int j, char *str)
{
	while (str[j])
	{
		if (data->quote_type == 'n' && (str[j] == '\'' || str[j] == '\"'))
		{
			data->quote_type = str[j++];
			data->quote_count++;
			if (str[j] == '\0')
				break ;
		}
		if (data->quote_type != 'n' && str[j] == data->quote_type)
			data->quote_type = count_quotes_2(data);
		if (str[j] == '$' && data->quote_type != '\'')
		{
			str = expander(data, str, j);
			if (str[0] == '\0')
				break ;
			if ((size_t) j >= (ft_strlen(str) - 1))
				j = 0;
		}
		j++;
	}
	if (check_odd_quotes(data->quote_count, data->quote_type) == 0)
		return (count_quotes_3(str));
	return (str);
}

int	validate_tokens(t_data *data, int i, t_lexer *node)
{
	int		len;

	len = get_lexer_len(data->lexer[0]);
	while (i < len)
	{
		if (node->token)
		{
			if (!node->next)
			{
				ft_printf("minishell: syntax error\n");
				g_exit_status = 2;
				return (0);
			}
			else if (node->next->token)
			{
				ft_printf("minishell: syntax error near unexpected "
					"token `%c'\n", node->next->token[0]);
				g_exit_status = 2;
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
				g_exit_status = 2;
				return (0);
			}
		}
		if (validate_tokens(data, 0, data->lexer[0]) == 0)
			return (0);
		parsing(data);
		return (1);
	}
	else
		return (0);
}
