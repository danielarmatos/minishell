/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:07:10 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/22 20:19:15 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void pipes(t_data *data, t_simple_cmds *simple_cmds)
{
	int fd[2];
	int	pid;
	int status;

	pipe(fd);
	pid = fork();
}*/

void execute_direct_path(t_simple_cmds *simple_cmds)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		if (execve(simple_cmds->cmds[0], simple_cmds->cmds, NULL) == -1)
			ft_printf("%s: command not found\n", simple_cmds->cmds[0]);
		exit (1);
	}
	else
		while (waitpid(pid, 0, WUNTRACED) == -1)
			;
}

/*int	execute_path(char *name, t_simple_cmds *simple_cmds)
{
	int result;
	int found;
	int pid;

	found = 0;
	result = access(name, F_OK);
	if (result == 0)
	{
		found = 1;
		pid = fork();
		if (!pid)
		{
			if (execve(name, simple_cmds->cmds, NULL) == -1)
				ft_printf("%s: command not found\n", simple_cmds->cmds[0]);
			exit (1);
		}
		else
			while (waitpid(pid, 0, WUNTRACED) == -1)
				;
	}
	return (found);
}*/

int	execute_path(char *name, t_simple_cmds *simple_cmds, int fd_in)
{
	int result;
	int found;

	found = 0;
	result = access(name, F_OK);
	if (result == 0)
	{
		found = 1;
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		if (execve(name, simple_cmds->cmds, NULL) == -1)
			ft_printf("%s: command not found\n", simple_cmds->cmds[0]);
	}
	return (found);
}


int	check_executable(t_data *data, t_simple_cmds *simple_cmds, int fd_in)
{
	(void)data;
	char 	*temp;
	char	**paths;
	char 	*name;
	int 	found;
	int		i;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		name = ft_strjoin(temp, simple_cmds->cmds[0]);
		found = execute_path(name, simple_cmds, fd_in);
		if (found == 1)
			break ;
		i++;
	}
	return (found);
}

int	parent_process_2(int *fd, int fd_in)
{
	while (waitpid(-1, 0, WUNTRACED) == -1)
		;
	ft_printf("Parent process\n");
	close(fd[1]);
	close(fd_in);
	fd_in = fd[0];
	return (fd_in);
}

void	child_process_2(int *fd)
{
	ft_printf("Child process\n");
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

int	ft_pipes_2(t_data *data, int fd_in, int *fd)
{
	(void)data;
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		ft_printf("Error opening the pipe\n");
		return (0);
	}
	pid = fork();
	if (pid < 0)
	{
		printf("Error\n");
		return (0);
	}
	if (pid == 0)
		child_process_2(fd);
	else
		fd_in = parent_process_2(fd, fd_in);
	//dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (fd_in);
}

int	execute(t_data *data, t_simple_cmds *simple_cmds)
{
	(void)data;
	int 	fd_in;
	int 	fd[2];
	int 	temp;

	temp = 1;
	fd_in = dup(STDIN_FILENO);
	while(simple_cmds)
	{
		temp++;
		if (simple_cmds->next != NULL)
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				check_executable(data, simple_cmds, fd_in);
				return (1);
			}
			else
			{
				close(fd[1]);
				close(fd_in);
				fd_in = fd[0];
			}
		}
		else
		{
			if (fork() == 0)
			{
				/*temp = dup(STDOUT_FILENO);
				dup2(temp, STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				check_executable(data, simple_cmds, fd_in);*/
				check_executable(data, simple_cmds, fd_in);
				return (1);
			}
			else
			{
				close(fd_in);
				while(waitpid(-1, NULL, WUNTRACED) != -1)
					;
				fd_in = dup(STDIN_FILENO);
			}
		if (simple_cmds->next != NULL)
			simple_cmds = simple_cmds->next;
		else
			break;
		}
	}
	close(fd_in);
	return (0);
}

/*int	execute(t_data *data, t_simple_cmds *simple_cmds)
{
	(void)data;
	int 	fd_in;
	int 	fd[2];

	fd_in = dup(STDIN_FILENO);
	while(simple_cmds)
	{
		if (simple_cmds->next != NULL)
			fd_in = ft_pipes_2(data, fd_in, fd);
		if (check_executable(data, simple_cmds) == 0)
			execute_direct_path(simple_cmds);
		if (simple_cmds->next != NULL)
			simple_cmds = simple_cmds->next;
		else
			break;
	}
	return (0);
}*/

/*
int	check_executable(t_data *data, t_simple_cmds *simple_cmds)
{
	(void)data;
	char	**paths;
	char 	*name;
	char 	*temp;
	int 	i;
	int 	found;

	if (simple_cmds->next != NULL)
	{
		ft_pipes(data, simple_cmds);
		return (0);
	}
	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		name = ft_strjoin(temp, simple_cmds->cmds[0]);
		found = execute_path(name, simple_cmds);
		if (found == 1)
			break ;
		i++;
	}
	if (found == 0)
		execute_direct_path(simple_cmds);
	return (0);
}
*/
