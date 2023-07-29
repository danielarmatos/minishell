/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:02:52 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/29 20:05:48 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
