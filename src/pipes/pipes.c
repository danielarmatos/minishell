/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:39:27 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/20 20:12:31 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}

void	exec(char *cmd, char **env)
{
	(void)cmd;
	(void)env;

	printf("Exec function\n");
}

void	parent_process(t_data *data, t_simple_cmds *simple_cmds, int *p_fd)
{
	//int	fd;
	(void)data;
	(void)simple_cmds;

	printf("\033[0;36mParent Process:\033[0m %s\n%i, %i\n", simple_cmds->cmds[0], p_fd[0], p_fd[1]);
/*	fd = open_file(argv[4], 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec(argv[3], env);*/
}

void	child_process(t_data *data, t_simple_cmds *simple_cmds, int *p_fd)
{
//	int		fd;
	(void)data;
	(void)simple_cmds;
	(void)p_fd;

	printf("\033[0;36mChild Process:\033[0m %s\n", simple_cmds->cmds[0]);
/*
	fd = open_file(argv[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(argv[2], env);*/
}

void	ft_pipes(t_data *data, t_simple_cmds *simple_cmds)
{
	(void)data;
	int   fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();
	if (pid < 0)
	{
		printf("Error\n");
		return ;
	}
	if (!pid)
		child_process(data, simple_cmds, fd);
	else
		parent_process(data, simple_cmds->next, fd);
}