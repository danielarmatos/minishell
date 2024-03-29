/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <dmanuel-@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:25:56 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/06/30 20:49:43 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	equals(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	check_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']' \
			|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.' \
			|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+' \
			|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!' \
			|| c == '~' \
			|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}

char	*delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], ft_strlen(str) - i);
		}
		i++;
	}
	return (str);
}

int	env_count(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
		i++;
	i = i - 1;
	return (i);
}

char	*check_varstr(char *str)
{
	char	*str2;
	size_t	i;

	i = 0;
	while (str[i] != '=')
		i++;
	str2 = malloc(sizeof(char) + i);
	ft_strlcpy(str2, str, i);
	return (str2);
}
