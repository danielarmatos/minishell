/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:23:06 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/30 19:35:17 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_data(t_data *data)
{
	free(data->prompt);
	data->prompt = NULL;
	free_lexer(data);
	free_simple_cmds(data);
	dup2(data->og_ioput[0], STDIN_FILENO);
	dup2(data->og_ioput[1], STDOUT_FILENO);
}

void	ft_exit_fork(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	free_data(data);
	exit(g_exit_status);
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
