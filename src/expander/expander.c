/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:53:39 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/20 19:19:27 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_variable(t_data *data, char *value)
{
	char	**str;
	int		j;

	j = 0;
	while (data->env[j])
	{
		str = ft_split(data->env[j], '=');
		if (ft_strncmp(value, str[0], ft_strlen(str[0]) + 1) == 0)
			return (str[1]);
		j++;
	}
	return (NULL);
}

char	*find_value(char *input)
{
	char	*variable;
	int		f;
	int		i;

	f = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			f = i + 1;
			while (input[i] && input[i] != ' ')
				i++;
			break ;
		}
		i++;
	}
	if (f != 0)
	{
		variable = ft_substr(input, f, (i - f));
		return (variable);
	}
	return (NULL);
}

void	expand_str(t_data *data, t_lexer *node)
{
	int		j;
	int		found;
	char	*variable;
	char	*result;
	char	*value;

	value = find_value(node->str);
	j = 0;
	found = 0;
	variable = find_variable(data, value);
	if (variable)
	{
		result = str_replace(node->str, value, variable);
		node->str = result;
	}
	else
		node->str = ft_strdup("");
}

void	expander(t_data *data, t_lexer *node)
{
	int				i;
	int				j;
	int				len;

	i = 0;
	j = 0;
	len = get_lexer_len(data->lexer[0]);
	while (i < len)
	{
		if (node->quote_type != 's')
		{
			if (node->str)
			{
				while (ft_strchr(node->str, '$') != 0)
				{
					expand_str(data, node);
				}
			}
		}
		if (node->next)
			node = node->next;
		i++;
	}
}
