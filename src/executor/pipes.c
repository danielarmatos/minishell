/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:30:37 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/08 18:45:38 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_pipes(t_data *data, t_simple_cmds *simple_cmds, int pipe_count)
{
	t_simple_cmds	*cmds;
	int				i;

	i = 0;
	cmds = simple_cmds;
	while (i < pipe_count)
	{
		if (cmds->redirections[0])
		{
			if (cmds->redirections[0]->token[0] == '<'
				&& cmds->redirections[0]->token[1] == '<')
			{
				dup2(data->fd, STDIN_FILENO);
				execute_redirection(data, cmds->redirections[0], 0);
			}
		}
		cmds = cmds->next;
		i++;
	}
}

void	setup_pipes(int pipes[][2], int pipe_count, t_simple_cmds \
	*simple_cmds, t_data *data)
{
	int	i;

	i = 0;
	heredoc_pipes(data, simple_cmds, pipe_count);
	set_signals(1);
	data->interactive = 1;
	handle_heredoc_signals(0, data);
	while (i < pipe_count)
	{
		pipe(pipes[i % 2]);
		i++;
		simple_cmds = simple_cmds->next;
	}
}

void	handle_child_processes(int pipes[][2], int pipe_count, t_data *data, \
t_simple_cmds *simple_cmds)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < pipe_count)
	{
		pipe(pipes[i % 2]);
		pid = fork();
		if (pid == 0)
		{
			set_signals(1);
			handle_heredoc_signals(0, data);
			setup_child_process(pipes, i, data, simple_cmds);
		}
		if (i > 0)
		{
			close(pipes[(i - 1) % 2][0]);
			close(pipes[(i - 1) % 2][1]);
		}
		i++;
		simple_cmds = simple_cmds->next;
	}
}

void	wait_and_cleanup(int pipes[][2], int pipe_count)
{
	int	i;
	int	child_status;

	i = 0;
	(void)pipes;
	child_status = 0;
	while (i < (pipe_count + 1))
	{
		wait(&child_status);
		if ((child_status >> 7) & 0x01)
			write(2, "minishell: Quit (core dump)\n", 28);
		if ((((child_status) & 0x7f) + 1) >> 1)
		{
			if (((child_status) & 0x7f) == 2)
				child_status = 130;
		}
		else
			child_status >>= 8;
		i++;
	}
}

void	ft_pipes(t_data *data, t_simple_cmds *simple_cmds)
{
	int	pipes[2][2];

	data->pipe_count = count_pipes(simple_cmds);
	setup_pipes(pipes, data->pipe_count, simple_cmds, data);
	handle_child_processes(pipes, data->pipe_count, data, simple_cmds);
	wait_and_cleanup(pipes, data->pipe_count);
}
