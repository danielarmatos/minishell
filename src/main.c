/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:50:22 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/02 20:39:58 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	*data;
	char	**input;

	data = malloc(sizeof(t_data));
	while (1)
	{
		data->prompt = readline("Minishell$ ");
		if (data->prompt != NULL)
			add_history(data->prompt);
		input = ft_split(data->prompt, ' ');
		if (ft_strncmp("pwd", input[0], 3) == 0)
			pwd(input);
		if (ft_strncmp("cd", input[0], 2) == 0)
			ft_cd(data, input);
		if (ft_strncmp("echo", input[0], 4) == 0)
			ft_echo(data, input);
	}
}
