/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <dmanuel-@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:06:50 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/05/26 15:06:50 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_error(t_simple_cmds *simple_cmd)
{
	int	i;

	i = 0;
	if (!simple_cmd->cmds[1])
	{
		ft_putendl_fd("Minishell: unset: not enough arguments", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	while (simple_cmd->cmds[1][i])
	{
		if (simple_cmd->cmds[1][i++])
		{

		}
	}
}