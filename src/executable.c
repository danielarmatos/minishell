/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:07:10 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/19 20:06:21 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

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

int	check_executable(t_data *data, t_simple_cmds *simple_cmds)
{
	(void)data;
	char	**paths;
	char 	*name;
	char 	*temp;
	int 	i;
	int 	result;
	int 	pid;
	int 	found;

	i = 0;
	found = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		name = ft_strjoin(temp, simple_cmds->cmds[0]);
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
			break ;
		}
		i++;
	}
	if (found == 0)
		execute_direct_path(simple_cmds);
	return (0);
}
