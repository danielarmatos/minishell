/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:39:27 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/21 20:12:06 by dreis-ma         ###   ########.fr       */
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

int	exec(t_data *data, t_simple_cmds *simple_cmds, int fd_in)
{
	(void)data;
	char	**paths;
	char 	*name;
	char 	*temp;
	int 	i;
	int 	found;

	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
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

void	parent_process(t_data *data, t_simple_cmds *simple_cmds, int *fd, int fd_in)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	exec(data, simple_cmds, fd_in);
	/*if (fork() == 0)
		exec(data, simple_cmds, fd_in);
	else
		while (waitpid(-1, 0, WUNTRACED) == -1)
			;*/
}

void	child_process(t_data *data, t_simple_cmds *simple_cmds, int *fd, int fd_in)
{
	//printf("\033[0;36mChild Process:\033[0m %s\n", simple_cmds->cmds[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec(data, simple_cmds, fd_in);
}

void	ft_pipes(t_data *data, t_simple_cmds *simple_cmds)
{
	(void)data;
	int		fd[2];
	int		fd_in;
	pid_t	pid;

	fd_in = dup(STDIN_FILENO);
	if (pipe(fd) == -1)
	{
		ft_printf("Error opening the pipe\n");
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		printf("Error\n");
		return ;
	}
	if (pid == 0)
		child_process(data, simple_cmds, fd, fd_in);
	else
		parent_process(data, simple_cmds->next, fd, fd[0]);
}