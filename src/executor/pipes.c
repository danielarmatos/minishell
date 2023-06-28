/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:20:13 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/28 16:28:54 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	p_process(t_data *data, t_simple_cmds *s_cmds, int id, int **pipe_fd)
{
	int	pid;

	while (s_cmds->next != NULL)
	{
		id++;
		s_cmds = s_cmds->next;
		if (s_cmds->next != NULL)
		{
			pipe_fd[id] = malloc(sizeof(int) * 2);
			pipe(pipe_fd[id]);
		}
		pid = fork();
		if (pid == 0)
		{
			if (pipe_fd[id])
				dup2(pipe_fd[id][1], STDOUT_FILENO);
			dup2(pipe_fd[id - 1][0], STDIN_FILENO);
			close_pipes(pipe_fd, id);
			if (s_cmds->redirections[0])
				execute_redirection(data, s_cmds->redirections[0]);
			if (check_builtins(data, s_cmds) == 0)
				check_executable(data, s_cmds);
			exit(0);
		}
	}
}

void	create_pipes(t_data *data, t_simple_cmds *simple_cmds, int **pipe_fd)
{
	int		id;
	pid_t	pid;

	id = 0;
	pipe_fd[id] = malloc(sizeof(int) * 2);
	pipe(pipe_fd[id]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_fd[id][1], STDOUT_FILENO);
		close_pipes(pipe_fd, id);
		if (simple_cmds->redirections[0])
			execute_redirection(data, simple_cmds->redirections[0]);
		if (check_builtins(data, simple_cmds) == 0)
			check_executable(data, simple_cmds);
		free(pipe_fd[0]);
		free(pipe_fd[1]);
		free(pipe_fd);
		ft_exit_fork(data);
	}
	else
		p_process(data, simple_cmds, id, pipe_fd);
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
	while (waitpid(-1, NULL, 0) != -1)
		;
	i = 0;
	while (i < pipe_count)
	{
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
}
