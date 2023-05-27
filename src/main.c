/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:50:22 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/27 14:00:35 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_data(t_data *data)
{
	free(data->prompt);
	free_lexer(data);
	free_simple_cmds(data);
}

int	check_builtins(t_data *data, t_simple_cmds *simple_cmd)
{
	int	found;

	found = 1;
	if (ft_strncmp("pwd", simple_cmd->cmds[0], 4) == 0)
		ft_pwd(data);
	//else if (ft_strncmp("cd", input[0], 3) == 0)
		//	ft_cd(data, input);
	else if (ft_strncmp("exit", simple_cmd->cmds[0], 5) == 0)
		ft_exit(data, simple_cmd);
	else if (ft_strncmp("echo", simple_cmd->cmds[0], 5) == 0)
		ft_echo(data, simple_cmd);
	else if (ft_strncmp("env", simple_cmd->cmds[0], 4) == 0)
		ft_env(data);
	else
		found = 0;
	return (found);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	data->env = envp;
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
		executor(data, data->simple_cmds[0]);
		clear_data(data);
	}
}
