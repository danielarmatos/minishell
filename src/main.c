/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:50:22 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/01 19:26:54 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	check_builtins_2(t_data *data, t_simple_cmds *simple_cmd)
{
	int	found;

	found = 1;
	if (ft_strncmp("pwd", simple_cmd->cmds[0], 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp("cd", simple_cmd->cmds[0], 3) == 0)
		ft_cd(data, simple_cmd);
	else if (ft_strncmp("exit", simple_cmd->cmds[0], 5) == 0)
		ft_exit(data, simple_cmd);
	else if (ft_strncmp("echo", simple_cmd->cmds[0], 5) == 0)
		ft_echo(data, simple_cmd);
	else if (ft_strncmp("env", simple_cmd->cmds[0], 4) == 0)
		ft_env(data);
	else if (ft_strncmp("export", simple_cmd->cmds[0], 7) == 0)
		ft_export(data, simple_cmd);
	else if (ft_strncmp("unset", simple_cmd->cmds[0], 6) == 0)
		ft_unset(data, simple_cmd);
	else
		found = 0;
	return (found);
}

int	check_builtins(t_data *data, t_simple_cmds *simple_cmd)
{
	if (!simple_cmd)
		return (0);
	else if (!simple_cmd->cmds)
		return (0);
	else if (!simple_cmd->cmds[0])
		return (0);
	else
		return (check_builtins_2(data, simple_cmd));
}

void	init_env(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
}

void	main_loop(t_data *data)
{
	while (1)
	{
		data->simple_cmds = NULL;
		data->lexer = NULL;
		data->fd = 0;
		data->interactive = 1;
		data->pipe_fd = NULL;
		set_signals(0);
		data->prompt = readline("Minishell$ ");
		set_signals(1);
		if (!data->prompt)
			close_minishell(data);
		if (data->prompt != NULL)
			add_history(data->prompt);
		if (lexical_analysis(data, data->prompt) == 1)
			if (data->lexer[0])
				executor(data, data->simple_cmds[0]);
		clear_data(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	data->og_ioput[0] = dup(STDIN_FILENO);
	data->og_ioput[1] = dup(STDOUT_FILENO);
	init_env(data, envp);
	find_pwd(data);
	g_exit_status = 0;
	main_loop(data);
}
