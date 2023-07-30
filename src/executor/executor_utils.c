/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:02:52 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/30 20:01:55 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**search_paths(t_data *data, t_simple_cmds *simple_cmds)
{
	char	*temp;
	char	**paths;

	if (!simple_cmds->cmds[0])
		return (0);
	temp = find_variable(data, "PATH");
	if (temp == NULL)
	{
		execute_direct_path(data, simple_cmds);
		return (0);
	}
	paths = ft_split(temp, ':');
	free(temp);
	return (paths);
}

void	free_direct_path(t_data *data)
{
	clear_data(data);
	free(data->pwd);
	free(data->oldpwd);
	free_arr(data->env);
	g_exit_status = 127;
	if (data->pipe_fd)
	{
		free(data->pipe_fd[0]);
		free(data->pipe_fd[1]);
		free(data->pipe_fd);
	}
	free(data);
}
