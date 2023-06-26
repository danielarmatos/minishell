/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <dmanuel-@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:49:20 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/06/15 11:54:54 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	var_exist(t_data *data, char *str)
{
	int	i;

	i = 0;
	if (str[equals(str)] == '\"')
		delete_quotes(str, '\"');
	if (str[equals(str)] == '\'')
		delete_quotes(str, '\'');
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], str, equals(data->env[i])) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	parameter(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (export_error(str));
	if (equals(str) == 0)
		return (EXIT_FAILURE);
	if (str[0] == '=')
		return (export_error(str));
	while (str[i] != '=')
	{
		if (check_identifier(str[i]))
			return (export_error(str));
		i++;
	}
	return (EXIT_SUCCESS);
}

static char	**whileloop_add_var(char **arr, char **var, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			var[i] = ft_strdup(str);
			var[i + 1] = ft_strdup(arr[i]);
		}
		else
			var[i] = ft_strdup(arr[i]);
		if (var[i] == NULL)
		{
			free_arr(var);
			return (var);
		}
		i++;
	}
	return (var);
}

static char	**add_var(char **arr, char *str)
{
	char	**var;
	size_t	i;

	i = 0;
	if (str[equals(str)] == '\"')
		delete_quotes(str, '\"');
	if (str[equals(str)] == '\'')
		delete_quotes(str, '\'');
	while (arr[i] != NULL)
		i++;
	var = ft_calloc(sizeof(char *), i + 2);
	if (!var)
		return (NULL);
	whileloop_add_var(arr, var, str);
	return (var);
}

int	ft_export(t_data *data, t_simple_cmds *simple_cmds)
{
	char	**temp;
	int		i;

	i = 1;
	if (!simple_cmds->cmds[1] || simple_cmds->cmds[1][0] == '\0')
		ft_env(data);
	else
	{
		while (simple_cmds->cmds[i])
		{
			if (parameter(simple_cmds->cmds[i]) == 0 && var_exist(data, \
				simple_cmds->cmds[i]) == 0)
			{
				if (simple_cmds->cmds[i])
				{
					temp = add_var(data->env, simple_cmds->cmds[i]);
					free_arr(data->env);
					data->env = temp;
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
