/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:23:26 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/02 16:41:02 by dreis-ma         ###   ########.fr       */
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
