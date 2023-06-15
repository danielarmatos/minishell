/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <dmanuel-@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:38:48 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/06/15 15:26:11 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_path(t_data *data)
{
	char	*tmp;

	ft_printf("Hello\n");
	tmp = ft_strdup(data->pwd);
	free(data->oldpwd);
	data->oldpwd = tmp;
	free(data->pwd);
	data->pwd = getcwd(NULL, sizeof(NULL));
}

void	add_path_env(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[1], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", data->pwd);
			free(data->env[i]);
			data->env[i] = tmp;
		}
		i++;
	}
}

char	*find_path(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp((data->env[i]), str, ft_strlen(str)))
			return (ft_substr(data->env[i], ft_strlen(str), ft_strlen
					(data->env[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(t_data *data, char *str)
{
	char	*tmp;
	int		path;

	tmp = find_path(str, data);
	path = chdir(tmp);
	free(tmp);
	if (path != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (0);
}

void	ft_cd(t_data *data, t_simple_cmds *simple_cmd)
{
	int	path;

	if (!simple_cmd->cmds[1])
		path = specific_path(data, "home=");
	else if (ft_strncmp(simple_cmd->cmds[1], "-", 1) == 0)
		path = specific_path(data, "oldpwd=");
	else
	{
		path = chdir(simple_cmd->cmds[1]);
		if (path != 0)
		{
			ft_printf("cd: no path\n");
		}
	}
	change_path(data);
	add_path_env(data);
}
