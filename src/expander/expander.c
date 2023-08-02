/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:53:39 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/01 22:08:02 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_variable(t_data *data, char *value)
{
	char	**str;
	char	*variable;
	int		j;

	j = 0;
	variable = NULL;
	while (data->env[j])
	{
		if (data->env[j] == NULL)
			return (NULL);
		if (data->env[j][ft_strlen(data->env[j]) - 1] == '=')
			return (NULL);
		str = ft_split(data->env[j], '=');
		if (!str[1])
			return (NULL);
		if (ft_strncmp(value, str[0], ft_strlen(str[0]) + 1) == 0)
		{
			variable = ft_strdup(str[1]);
			free_str(str);
			break ;
		}
		j++;
		free_str(str);
	}
	if (variable)
		return (variable);
	return (NULL);
}

char	*find_value(char *input, int i)
{
	int		f;

	while (input[i])
	{
		if (input[i] == '$')
			break ;
		i++;
	}
	i++;
	f = i;
	if (input[i] != '?')
	{
		while (input[i])
		{
			if (ft_isalnum(input[i]) == 0)
				break ;
			i++;
		}
	}
	else
		i++;
	if (i == f)
		return (NULL);
	return (ft_substr(input, f, (i - f)));
}

char	*expand_str(t_data *data, char *str)
{
	char	*variable;
	char	*value;
	char	*str2;

	value = find_value(str, 0);
	if (!value)
	{
		free(str);
		str2 = ft_strdup("");
		return (str2);
	}
	variable = find_variable(data, value);
	if (variable)
		str2 = str_replace(str, value, variable);
	else
		str2 = ft_strdup("");
	free(value);
	free(variable);
	free(str);
	return (str2);
}

int	check_here_doc(t_data *data)
{
	int		len;
	int		j;
	t_lexer	*node;

	if (!data->lexer[0])
		return (1);
	node = data->lexer[0];
	len = get_lexer_len(data->lexer[0]);
	j = 0;
	while (j < len)
	{
		if (node->next)
			node = node->next;
		j++;
	}
	if (node->token)
		if (node->token[0] == '<' && node->token[1] == '<')
			return (0);
	return (1);
}

char	*expander(t_data *data, char *input, int i)
{
	char	*value;
	char	*variable;
	char	*input2;

	if (check_here_doc(data) == 0)
		return (input);
	value = find_value(input, i);
	if (!value)
	{
		free(input);
		input2 = ft_strdup("");
		return (input2);
	}
	variable = find_variable(data, value);
	if (variable)
		input2 = str_replace(input, value, variable);
	else
	{
		if (ft_strncmp("?", value, 2) == 0)
		{
			variable = ft_itoa(g_exit_status);
			input2 = str_replace(input, value, variable);
		}
		else
			input2 = str_replace(input, value, "");
	}
	free(value);
	free(variable);
	free(input);
	return (input2);
}
