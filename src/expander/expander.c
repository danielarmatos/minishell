/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:53:39 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/19 20:59:12 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trim_str(char *result)
{
	int	i;

	i = 0;
	while (result[i] && result[i] != '\"')
		i++;
	result = ft_substr(result, 0, i);
	ft_printf("RESULT2:\n%s\n\n", result);
	return (result);
}

char	*d_quotes_expand_str(t_data *data, char *variable, char *input)
{
	int		j;
	int		found;
	char	**str;
	char	*result;

	j = 0;
	found = 0;
	while (data->env[j])
	{
		str = ft_split(data->env[j], '=');
		if (ft_strncmp(variable, str[0], ft_strlen(str[0])) == 0)
		{
			found = 1;
			break ;
		}
		j++;
	}
	if (found == 1)
	{
		result = str_replace(input, variable, str[1]);
		return (trim_str(result));
	}
	free(str[0]);
	return (NULL);
}

char	*d_quotes_expander(t_data *data, char *input, int i, int j)
{
	(void)data;
	char	*variable;
	//char 	*result;
	int		f;

	f = 0;
	while (i <= j)
	{
		if (input[i] == '$')
		{
			f = i + 1;
			while (i <= j && input[i] != ' ' && input[i] && input[i] != '\"')
				i++;
			break ;
		}
		i++;
	}
	if (f != 0)
	{
		variable = ft_substr(input, f, (i - f));
	//	result = str_replace(d_quotes_expand_str(data, variable));
		//return (result);
		return (d_quotes_expand_str(data, variable, input));

	}
	return (NULL);
}

void	expand_str(t_data *data, t_simple_cmds *simple_cmds, int i)
{
	int		j;
	int		found;
	char	**str;
	char 	*variable;

	j = 0;
	found = 0;
	variable = simple_cmds->cmds[i];
	variable++;
	while (data->env[j])
	{
		str = ft_split(data->env[j], '=');
		if (ft_strncmp(variable, str[0], ft_strlen(str[0])) == 0)
		{
			found = 1;
			break ;
		}
		j++;
	}
	if (found == 1)
	{
		//free(simple_cmds->cmds[i]);
		simple_cmds->cmds[i] = str[1];
	}
	free(str[0]);
	/*else
	{
		free(str[0]);
		free(str[1]);
		free(str);
	}*/
}

void	expander(t_data *data, t_simple_cmds *simple_cmds)
{
	int				i;
	int				j;
	int				len;
	t_simple_cmds	*node;

	i = 0;
	j = 0;
	len = 0;
	if (simple_cmds)
		len = count_pipes(simple_cmds);
	node = simple_cmds;
	while (i < len)
	{
		while (node->cmds[j])
		{
			if (node->cmds[j][0] == '$' && node->cmds[j][1])
				expand_str(data, node, j);
			j++;
		}
		if (node->next)
			node = node->next;
		i++;
	}
}
