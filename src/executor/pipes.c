/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:30:37 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/07 11:06:43 by dmanuel-         ###   ########.fr       */
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
				execute_redirection(data, cmds->redirections[0]);
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
	while (i < pipe_count)
	{
		wait(&child_status);
		if (WIFEXITED(child_status))
			g_exit_status = WEXITSTATUS(child_status);
		else if (WIFSIGNALED(child_status))
			g_exit_status = 128 + WTERMSIG(child_status);
		i++;
	}
}

void	ft_pipes(t_data *data, t_simple_cmds *simple_cmds)
{
	int	pipes[2][2];

	data->pipe_count = count_pipes(simple_cmds);
	setup_pipes(pipes, data->pipe_count, simple_cmds, data);
	handle_child_processes(pipes, data->pipe_count, data, simple_cmds);
	/*close_unused_pipes(pipes, data->pipe_count);*/
	wait_and_cleanup(pipes, data->pipe_count);
}

/*
void ft_pipes(t_data *data, t_simple_cmds *simple_cmds)
{
	int pipes[2][2];
	int i;
	pid_t pid;
	int pipe_count;
	int child_status;

	i = 0;
	pipe_count = count_pipes(simple_cmds);
	heredoc_pipes(data, simple_cmds, pipe_count);
	while (i < pipe_count)
	{
		pipe(pipes[i % 2]);
		pid = fork();
		if (pid == 0)
		{
			if (i > 0) {
				dup2(pipes[(i - 1) % 2][0], STDIN_FILENO);
				close(pipes[(i - 1) % 2][0]);
				close(pipes[(i - 1) % 2][1]);
			}
			if (i < pipe_count - 1) {
				dup2(pipes[i % 2][1], STDOUT_FILENO);
				close(pipes[i % 2][0]);
				close(pipes[i % 2][1]);
			}
			if (simple_cmds->redirections[0])
			{
				if (!(simple_cmds->redirections[0]->token[0] == '<' &&
					simple_cmds->redirections[0]->token[1] == '<'))
					execute_redirection(data, simple_cmds->redirections[0]);
			}
			if (check_builtins(data, simple_cmds) == 0)
				check_executable(data, simple_cmds);
			exit(EXIT_FAILURE);
		}
		if (i > 0)
		{
			close(pipes[(i - 1) % 2][0]);
			close(pipes[(i - 1) % 2][1]);
		}
		i++;
		simple_cmds = simple_cmds->next;
	}
	if (pipe_count > 1) {
		close(pipes[(pipe_count - 2) % 2][0]);
		close(pipes[(pipe_count - 2) % 2][1]);
	}
	i = 0;
	while (i < pipe_count)
	{
		wait(&child_status);
		if (WIFEXITED(child_status))
			g_exit_status = WEXITSTATUS(child_status);
		else if (WIFSIGNALED(child_status))
			g_exit_status = 128 + WTERMSIG(child_status);
		i++;
	}
}
*/
