/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:38:48 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/08/01 14:44:50 by dmanuel-         ###   ########.fr       */
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
		if (!ft_strncmp(data->env[i], str, ft_strlen(str)))
			return (ft_substr(data->env[i], ft_strlen(str), \
					ft_strlen(data->env[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(t_data *data, char *str, int print)
{
	char	*tmp;
	int		path;

	tmp = find_path(str, data);
	if (tmp == NULL)
		path = 0;
	else
		path = chdir(tmp);
	if (print == 1 && path != 0)
		printf("%s\n", tmp);
	if (path != 0 || tmp == NULL)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	free(tmp);
	return (path);
}

int	ft_cd(t_data *data, t_simple_cmds *simple_cmd)
{
	int	path;

	if (!simple_cmd->cmds[1])
		path = specific_path(data, "HOME=", 0);
	else if (ft_strncmp(simple_cmd->cmds[1], "-", 1) == 0)
		path = specific_path(data, "OLDPWD=", 1);
	else
	{
		path = chdir(simple_cmd->cmds[1]);
		if (path != 0)
			ft_printf("minishell: cd: No such file or directory\n");
	}
	if (path != 0)
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	g_exit_status = 0;
	change_path(data);
	add_path_env(data);
	return (g_exit_status);
}
