/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:50:22 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/13 18:44:51 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_data(t_data *data)
{
	free(data->prompt);
	data->prompt = NULL;
	free_lexer(data);
	free_simple_cmds(data);
}

int	check_builtins(t_data *data, t_simple_cmds *simple_cmd)
{
	int	found;

	found = 1;
/*	if (simple_cmd->redirections[0])
		execute_redirection(simple_cmd->redirections[0]);*/
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

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	init_env(data, envp);
	data->simple_cmds = NULL;
	data->lexer = NULL;
	find_pwd(data);
	set_signals();
	while (1)
	{
		data->prompt = readline("Minishell$ ");
		if (!data->prompt)
			close_minishell(data);
		data->exit_status = EXIT_SUCCESS;
		if (data->prompt != NULL)
			add_history(data->prompt);
		lexical_analysis(data);
		if (data->lexer[0])
			executor(data, data->simple_cmds[0]);
		clear_data(data);
	}
}
