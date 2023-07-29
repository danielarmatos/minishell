/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:19:09 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/07/25 12:42:37 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**whileloop_del_var(char **arr, char **ret, char *cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		if (!(ft_strncmp(arr[i], cmds, equals(arr[i]) - 1) == 0 \
			&& arr[i][ft_strlen(cmds)] == '='))
		{
			ret[j] = ft_strdup(arr[i]);
			if (ret[j] == NULL)
			{
				free_arr(ret);
				return (ret);
			}
			j++;
		}
		i++;
	}
	return (ret);
}

char	**del_var(char **arr, char *cmd)
{
	char	**ret;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	ret = ft_calloc(sizeof(char *), i + 1);
	if (!ret)
		return (NULL);
	ret = whileloop_del_var(arr, ret, cmd);
	return (ret);
}

int	ft_unset(t_data *data, t_simple_cmds *simple_cmds)
{
	char	**tmp;

	g_exit_status = 0;
	if (unset_error(simple_cmds) == 1)
		return (EXIT_FAILURE);
	else if (data->exporting == 1)
		error_status(data, 3, "unset");
	else
	{
		tmp = del_var(data->env, simple_cmds->cmds[1]);
		free_arr(data->env);
		data->env = tmp;
	}
	return (EXIT_SUCCESS);
}
