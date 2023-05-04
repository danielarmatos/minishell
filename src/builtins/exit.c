/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:17:09 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/04 17:15:34 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Exit status parameters:
   EXIT_FAILURE - Program terminated unsuccessfully;
   EXIT_SUCCESS - Program terminated successfully. */

void free_data(t_data *data, char **input)
{
	int	i;

	i = 0;
	free(data->prompt);
	free(data);
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
	clear_history();
}

void	ft_exit(t_data *data, char **input)
{
	int	exit_status;
	if (input[0][4] != '\0')
		ft_printf("zsh: command not found: %s\n", input[0]);
	else
	{
		exit_status = data->exit_status;
		free_data(data, input);
		exit(exit_status);
	}
}