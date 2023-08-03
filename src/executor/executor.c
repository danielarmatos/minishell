/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:07:10 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/02 21:46:50 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_direct_path(t_data *data, t_simple_cmds *simple_cmds)
{
	if (execve(simple_cmds->cmds[0], simple_cmds->cmds, data->env) == -1)
	{
		if (simple_cmds->cmds[0][0] == ' ')
			ft_printf("\n");
		if (simple_cmds->cmds[0][0] == 0)
			ft_printf("\n");
		else
		{
			ft_putstr_fd(simple_cmds->cmds[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			g_exit_status = 127;
		}
		free_direct_path(data);
		exit (g_exit_status);
	}
}

int	execute_path(t_data *data, char *name, t_simple_cmds *simple_cmds)
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
		else if (execve(name, simple_cmds->cmds, data->env) == -1)
		{
			ft_putstr_fd(simple_cmds->cmds[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			g_exit_status = 127;
		}
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

	i = 0;
	paths = search_paths(data, simple_cmds);
	if (paths == NULL)
		return (0);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		name = ft_strjoin(temp, simple_cmds->cmds[0]);
		found = execute_path(data, name, simple_cmds);
		free(temp);
		free(name);
		if (found == 1)
			break ;
		i++;
	}
	free_str(paths);
	if (found == 0)
		execute_direct_path(data, simple_cmds);
	return (found);
}

int	executor_2(t_data *data, t_simple_cmds *simple_cmds, int fd_in, int fd_out)
{
	if (fork() == 0)
	{
		if (simple_cmds->redirections[0]
			&& (execute_redirection(data, simple_cmds->redirections[0]) == 0))
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
		if (simple_cmds->redirections[0] == NULL)
			set_signals(2);
		close(fd_in);
		while (waitpid(-1, &g_exit_status, WNOHANG) == 0)
			;
		g_exit_status = WEXITSTATUS(g_exit_status);
		set_signals(0);
	}
	return (0);
}

int	executor(t_data *data, t_simple_cmds *simple_cmds)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
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
