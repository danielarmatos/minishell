/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <dmanuel-@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:41:42 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/08/01 09:53:03 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		ft_putendl_fd(data->env[i], STDOUT_FILENO);
		i++;
	}
	g_exit_status = 0;
	return (g_exit_status);
}

char	**env_cpy(char **dup, int count)
{
	int		i;
	int		j;
	char	*sorting;

	i = 0;
	sorting = 0;
	while (i <= count)
	{
		j = i + 1;
		while (j <= count)
		{
			if (ft_strcmp(dup[i], dup[j]) > 0)
			{
				sorting = dup[i];
				dup[i] = dup[j];
				dup[j] = sorting;
			}
			j++;
		}
		i++;
	}
	return (dup);
}

char	**dup_env(t_data *data, char **dup)
{
	int	i;

	i = 0;
	while (data->env[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (data->env[i])
	{
		dup[i] = ft_strdup(data->env[i]);
		i++;
	}
	return (dup);
}

void	print_export_env(char **dup, int i, int j)
{
	int	eq;

	while (dup[i])
	{
		write(1, "declare -x ", 11);
		eq = 0;
		while (dup[i][j])
		{
			write(1, &dup[i][j], 1);
			if (dup[i][j] == 61 && eq == 0)
			{
				write(1, "\"", 1);
				eq = 1;
			}
			j++;
		}
		if (eq == 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
		j = 0;
		i++;
	}
}

void	export_env(t_data *data)
{
	char	**dup;
	int		count;

	if (data->exporting == 0)
	{
		dup = 0;
		dup = dup_env(data, dup);
		count = env_count(data);
		dup = env_cpy(dup, count);
		print_export_env(dup, 0, 0);
		free_arr(dup);
	}
	else
		error_status(data, 3, "export");
}
