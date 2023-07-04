/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <dmanuel-@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:41:42 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/07/03 12:31:11 by dmanuel-         ###   ########.fr       */
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
	return (0);
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
			if (strcmp(dup[i], dup[j]) > 0)
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
	dup = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (data->env[i])
	{
		dup[i] = ft_strdup(data->env[i]);
		i++;
	}
	return (dup);
}

void	print_export_env(char **dup)
{
	int	i;

	i = 0;
	printf("%s", "env print\n");
	while (dup[i])
	{
		printf("declare -x %s %s", dup[i], "\n");
		i++;
	}
}

void	export_env(t_data *data)
{
	char	**dup;
	int		count;

	dup = 0;
	dup = dup_env(data, dup);
	count = env_count(data);
	dup = env_cpy(dup, count);
	print_export_env(dup);
}
