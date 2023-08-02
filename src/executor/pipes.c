/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:30:37 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/02 19:24:46 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	p_process_2(t_data *data, t_simple_cmds *s_cmds, int id, int **pipe_fd)
{
	close_pipes(pipe_fd, id);
	if (check_builtins(data, s_cmds) == 0)
		check_executable(data, s_cmds);
	if (pipe_fd)
		free_pipe_fd(pipe_fd);
	ft_exit_fork(data);
	exit(g_exit_status);
}

void	p_process(t_data *data, t_simple_cmds *s_cmds, int id, int **pipe_fd)
{
	while (s_cmds->next != NULL)
	{
		id++;
		s_cmds = s_cmds->next;
		dup2(data->og_ioput[0], STDIN_FILENO);
		if (s_cmds->next != NULL)
		{
			pipe_fd[id] = malloc(sizeof(int) * 2);
			pipe(pipe_fd[id]);
		}
		else
			dup2(data->og_ioput[1], STDOUT_FILENO);
		if (pipe_fd[id])
			dup2(pipe_fd[id][1], STDOUT_FILENO);
		dup2(pipe_fd[id - 1][0], STDIN_FILENO);
		if (s_cmds->redirections[0])
			execute_redirection(data, s_cmds->redirections[0]);
		if (fork() == 0)
			p_process_2(data, s_cmds, id, pipe_fd);
	}
}

int	c_process_1(t_data *data, t_simple_cmds *simple_cmds)
{
	if (simple_cmds->redirections[0])
		return (execute_redirection(data, simple_cmds->redirections[0]));
	return (1);
}

int	create_pipes(t_data *data, t_simple_cmds *simple_cmds, int **pipe_fd)
{
	int		id;

	id = 0;
	set_signals(1);
	handle_heredoc_signals(0, data);
	pipe_fd[id] = malloc(sizeof(int) * 2);
	pipe(pipe_fd[id]);
	data->pipe_fd = pipe_fd;
	if (c_process_1(data, simple_cmds) == 0)
		return (0);
	dup2(pipe_fd[id][1], STDOUT_FILENO);
	if (fork() == 0)
	{
		close_pipes(pipe_fd, id);
		if (check_builtins(data, simple_cmds) == 0)
			check_executable(data, simple_cmds);
		free_pipe_fd(pipe_fd);
		ft_exit_fork(data);
	}
	else
		p_process(data, simple_cmds, id, pipe_fd);
	return (0);
}

void	ft_pipes(t_data *data, t_simple_cmds *simple_cmds)
{
	int	**pipe_fd;
	int	pipe_count;
	int	i;

	pipe_count = count_pipes(simple_cmds);
	pipe_fd = ft_calloc((pipe_count + 1), sizeof(int *));
	if (!pipe_fd)
		return ;
	create_pipes(data, simple_cmds, pipe_fd);
	close_pipes(pipe_fd, pipe_count);
	while (waitpid(-1, &g_exit_status, 0) != -1)
		;
	g_exit_status = g_exit_status / 256;
	while (waitpid(-1, 0, 0) != -1)
		;
	i = 0;
	while (i < pipe_count)
	{
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
}
