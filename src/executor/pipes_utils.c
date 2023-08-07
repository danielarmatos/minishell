/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:23:26 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/07 11:44:13 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipe_fd(int **pipe_fd)
{
	free(pipe_fd[0]);
	free(pipe_fd[1]);
	free(pipe_fd);
}

void	close_pipes(int **pipe_fd, int id)
{
	while (id >= 0)
	{
		if (pipe_fd[id])
		{
			close(pipe_fd[id][0]);
			close(pipe_fd[id][1]);
		}
		id--;
	}
}

int	count_pipes(t_simple_cmds *simple_cmds)
{
	t_simple_cmds	*node;
	int				i;

	i = 1;
	node = simple_cmds;
	while (node->next != NULL)
	{
		node = node->next;
		i++;
	}
	return (i);
}

void	setup_child_process(int pipes[][2], int i, t_data *data, \
							t_simple_cmds *simple_cmds)
{
	if (i > 0)
	{
		dup2(pipes[(i - 1) % 2][0], STDIN_FILENO);
		close(pipes[(i - 1) % 2][0]);
		close(pipes[(i - 1) % 2][1]);
	}
	if (i < data->pipe_count - 1)
	{
		dup2(pipes[i % 2][1], STDOUT_FILENO);
		close(pipes[i % 2][0]);
		close(pipes[i % 2][1]);
	}
	if (simple_cmds->redirections[0] && \
		!(simple_cmds->redirections[0]->token[0] \
		== '<' && simple_cmds->redirections[0]->token[1] == '<'))
		execute_redirection(data, simple_cmds->redirections[0]);
	if (check_builtins(data, simple_cmds) == 0)
		check_executable(data, simple_cmds);
	exit(EXIT_FAILURE);
}
