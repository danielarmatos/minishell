/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:07:10 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/28 18:12:34 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_direct_path(t_data *data, t_simple_cmds *simple_cmds)
{
	if (execve(simple_cmds->cmds[0], simple_cmds->cmds, NULL) == -1)
	{
		(void)data;
		if (simple_cmds->cmds[0][0] == ' ')
			ft_printf("\n");
		else
			ft_printf("%s: command not found\n", simple_cmds->cmds[0]);
		clear_data(data);
		//free(data->prompt);
		free(data->pwd);
		free(data->oldpwd);
		free(data);
		// There are some leaks here
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
		if (simple_cmds->cmds[0][0] == ' ')
			ft_printf("\n");
		else if (execve(name, simple_cmds->cmds, NULL) == -1)
			ft_printf("%s: command not found\n", simple_cmds->cmds[0]);
	}
	return (found);
}

int	check_executable(t_data *data, t_simple_cmds *simple_cmds)
{
	char	*temp;
	char	**paths;
	char	*name;
	int		found;
	int		i;

	(void)data;
	i = 0;
	//paths = ft_split(getenv("PATH"), ':');
	paths = ft_split(find_variable(data, "PATH"), ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		name = ft_strjoin(temp, simple_cmds->cmds[0]);
		found = execute_path(name, simple_cmds);
		free(temp);
		free(name);
		if (found == 1)
			break ;
		i++;
	}
	if (found == 0)
		execute_direct_path(data, simple_cmds);
	return (found);
}

/*int	executor_2(t_data *data, t_simple_cmds *simple_cmds, int fd_in, int fd_out)
{
	if (simple_cmds->redirections[0])
	{
		if (fork() == 0)
		{
			if (execute_redirection(data, simple_cmds->redirections[0]) == 0)
			{
				ft_exit_fork(data);
				return (0);
			}
			if (check_builtins(data, simple_cmds) == 0)
				check_executable(data, simple_cmds);
			dup2(fd_out, STDOUT_FILENO);
			ft_exit_fork(data);
		}
		else
		{
			close(fd_in);
			while (waitpid(-1, NULL, WUNTRACED) != -1)
				;
		}
	}
	else
		if (check_builtins(data, simple_cmds) == 0)
			check_executable(data, simple_cmds);
	return (0);
}*/

int	executor_2(t_data *data, t_simple_cmds *simple_cmds, int fd_in, int fd_out)
{
	if (fork() == 0)
	{
		if (simple_cmds->redirections[0])
			if (execute_redirection(data, simple_cmds->redirections[0]) == 0)
			{
				ft_exit_fork(data);
				return (0);
			}
		if (check_builtins(data, simple_cmds) == 0)
			check_executable(data, simple_cmds);
		dup2(fd_out, STDOUT_FILENO);
		ft_exit_fork(data);
	}
	else
	{
		close(fd_in);
		while (waitpid(-1, NULL, WUNTRACED) != -1)
			;
	}
	return (0);
}

int	executor(t_data *data, t_simple_cmds *simple_cmds)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	//expander(data, simple_cmds);
	if (simple_cmds->next != NULL)
		ft_pipes(data, simple_cmds);
	else
	{
		if (!simple_cmds->redirections[0])
		{
			if (check_builtins(data, simple_cmds) == 0)
				executor_2(data, simple_cmds, fd_in, fd_out);
		}
		else
			executor_2(data, simple_cmds, fd_in, fd_out);
	}
	close(fd_in);
	return (0);
}
