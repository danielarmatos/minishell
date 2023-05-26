/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:39:27 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/24 19:02:24 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_path_p(char *name, t_simple_cmds *simple_cmds)
{
	int result;
	int found;

	found = 0;
	result = access(name, F_OK);
	if (result == 0)
	{
		found = 1;
		execve(name, simple_cmds->cmds, NULL);
	}
	return (found);
}

int	exec(t_data *data, t_simple_cmds *simple_cmds)
{
	(void)data;
	char	**paths;
	char 	*name;
	char 	*temp;
	int 	i;
	int 	found;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		name = ft_strjoin(temp, simple_cmds->cmds[0]);
		found = execute_path_p(name, simple_cmds);
		if (found == 1)
			break ;
		i++;
	}
	if (found == 0)
		execute_direct_path(simple_cmds);
	return (0);
}

static void	close_pipes(int **pipe_fd, int id)
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

void create_pipes(t_data *data, t_simple_cmds *simple_cmds, int **pipe_fd)
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
		exec(data, simple_cmds);
		exit(0);
	}
	else
	{
		while (simple_cmds->next != NULL)
		{
			id++;
			simple_cmds = simple_cmds->next;
			if (simple_cmds->next != NULL)
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
				exec(data, simple_cmds);
				exit(0);
			}
		}
	}
}

int	count_pipes(t_simple_cmds *simple_cmds)
{
	t_simple_cmds	*node;
	int				i;

	i = 1;
	node = simple_cmds;
	while(node->next != NULL)
	{
		node = node->next;
		i++;
	}
	return (i);
}

void	ft_pipes(t_data *data, t_simple_cmds *simple_cmds)
{
	(void)data;
	int	**pipe_fd;
	int pipe_count;

	pipe_count = count_pipes(simple_cmds);
	pipe_fd = ft_calloc((pipe_count + 1), sizeof(int *));
	if (!pipe_fd)
		return ;
	create_pipes(data, simple_cmds, pipe_fd);
	close_pipes(pipe_fd, pipe_count);
	while (waitpid(-1, NULL, 0) != -1)
		;
}