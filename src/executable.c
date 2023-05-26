/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:07:10 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/24 19:32:45 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_direct_path(t_simple_cmds *simple_cmds)
{
	if (execve(simple_cmds->cmds[0], simple_cmds->cmds, NULL) == -1)
	{
		ft_printf("%s: command not found\n", simple_cmds->cmds[0]);
		exit (1);
	}
}

int	execute_path(char *name, t_simple_cmds *simple_cmds)
{
	int	result;
	int	found;

	found = 0;
	result = access(name, F_OK);
	if (result == 0)
	{
		found = 1;
		//dup2(fd_in, STDIN_FILENO);
		//close(fd_in);
		if (execve(name, simple_cmds->cmds, NULL) == -1)
			ft_printf("%s: command not found\n", simple_cmds->cmds[0]);
	}
	if (found == 0)
		execute_direct_path(simple_cmds);
	return (0);
}

int	check_executable(t_data *data, t_simple_cmds *simple_cmds)
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
		found = execute_path(name, simple_cmds);
		if (found == 1)
			break ;
		i++;
	}
	return (found);
}

int	execute(t_data *data, t_simple_cmds *simple_cmds)
{
	(void)data;
	int 	fd_in;
	//int 	fd[2];
	int 	temp;

	temp = 1;
	fd_in = dup(STDIN_FILENO);
	if (simple_cmds->next != NULL)
		ft_pipes(data, simple_cmds);
	else
	{
		if (fork() == 0)
		{
			check_executable(data, simple_cmds);
			return (1);
		}
		else
		{
			close(fd_in);
			while(waitpid(-1, NULL, WUNTRACED) != -1)
				;
		}
	}
	close(fd_in);
	return (0);
}
