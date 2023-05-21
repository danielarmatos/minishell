/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:07:10 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/21 20:02:08 by dreis-ma         ###   ########.fr       */
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

int	execute_path(char *name, t_simple_cmds *simple_cmds)
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
}
/*

int	check_executable(t_data *data, t_simple_cmds *simple_cmds)
{
	(void)data;
	char	**paths;
	char 	*name;
	char 	*temp;
	int 	i;
	int 	found;
	int 	fd_in;
	int 	fd[2];

	fd_in = STDIN_FILENO;
	while(simple_cmds)
	{
		if (simple_cmds->next != NULL)
			//abre os pipe channels
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
		if (simple_cmds->next != NULL)
			simple_cmds = simple_cmds->next;
		else
			break;
	}
	return (0);
}

*/


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

