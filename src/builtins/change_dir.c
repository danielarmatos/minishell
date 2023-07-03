/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:38:48 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/06/29 10:35:30 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_path(t_data *data)
{
	char	*tmp;

	tmp = ft_strdup(data->pwd);
	free(data->oldpwd);
	data->oldpwd = tmp;
	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
}

void	add_path_env(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", data->pwd);
			free(data->env[i]);
			data->env[i] = tmp;
		}
		else if (!ft_strncmp(data->env[i], "OLDPWD=", 7) && data->oldpwd)
		{
			tmp = ft_strjoin("OLDPWD=", data->oldpwd);
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
			return (ft_substr(data->env[i], ft_strlen(str), \
					ft_strlen(data->env[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(t_data *data, char *str)
{
	char	*tmp;
	int		path;

	tmp = ft_strdup(find_path(str, data));
	path = chdir(tmp);
	free(tmp);
	if (path != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (path);
}

int	ft_cd(t_data *data, t_simple_cmds *simple_cmd)
{
	int	path;

	if (!simple_cmd->cmds[1])
		path = specific_path(data, "HOME=");
	else if (ft_strncmp(simple_cmd->cmds[1], "-", 1) == 0)
		path = specific_path(data, "OLDPWD=");
	else
	{
		path = chdir(simple_cmd->cmds[1]);
		if (path != 0)
		{
			ft_printf("cd: no path\n");
		}
	}
	if (path != 0)
		return (EXIT_FAILURE);
	change_path(data);
	add_path_env(data);
	return (EXIT_SUCCESS);
}
