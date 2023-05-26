/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:17:09 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/26 16:50:14 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data(t_data *data, t_simple_cmds *simple_cmd)
{
	(void)simple_cmd;
	int	i;

	i = 0;
	free(data->prompt);
	free(data->env);
	free(data->pwd);
	free(data->oldpwd);
	free(data);
	/*if (simple_cmd->cmds[0])
	{
		while (simple_cmd->cmds[i])
		{
			free(simple_cmd->cmds[i]);
			i++;
		}
		free(simple_cmd->cmds);
	}*/
	//limpar data->simple_cmd;
	clear_history();
}

void	ft_exit(t_data *data, t_simple_cmds *simple_cmd)
{
	int	exit_status;

	if (simple_cmd->cmds && simple_cmd->cmds[0][4] != '\0')
		ft_printf("minishell: command not found: %s\n", simple_cmd->cmds[0]);
	else
	{
		exit_status = data->exit_status;
		free_data(data, simple_cmd);
		exit(exit_status);
	}
}
