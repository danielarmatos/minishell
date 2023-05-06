/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:50:22 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/04 20:59:52 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_data *data, char **input)
{
	if (ft_strncmp("pwd", input[0], 4) == 0)
		ft_pwd(data, input);
	if (ft_strncmp("cd", input[0], 3) == 0)
		ft_cd(data, input);
	if (ft_strncmp("exit", input[0], 5) == 0)
		ft_exit(data, input);
	if (ft_strncmp("echo", input[0], 5) == 0)
		ft_echo(data, input);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	**input;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	data->env = envp;
	set_signals();
	while (1)
	{
		data->prompt = readline("Minishell$ ");
		if (!data->prompt)
			ft_exit(data, 0);
		data->exit_status = EXIT_SUCCESS;
		if (data->prompt != NULL)
			add_history(data->prompt);
		input = ft_split(data->prompt, ' ');
		check_builtins(data, input);
	}
}
