/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:23:06 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/02 19:09:32 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_fork(t_data *data)
{
	int	exit_status;
	int	i;

	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	exit_status = data->exit_status;
	free_data(data);
	exit(exit_status);
}

void	free_redirections(t_simple_cmds *simple_cmd)
{
	int		len;
	int		i;
	t_lexer	*node;

	i = 0;
	len = 0;
	if (simple_cmd->redirections[0])
		len = get_lexer_len(simple_cmd->redirections[0]);
	while (i < len)
	{
		node = simple_cmd->redirections[0];
		if (node->next)
			simple_cmd->redirections[0] = simple_cmd->redirections[0]->next;
		free(node);
		i++;
	}
	free(simple_cmd->redirections);
	simple_cmd->redirections = NULL;
}
