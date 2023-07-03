/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:46:18 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/12 18:15:18 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	**create_redirections(void)
{
	t_lexer	**redirections;

	redirections = malloc(sizeof(t_lexer));
	if (!redirections)
		return (0);
	(*redirections) = 0;
	return (redirections);
}

t_simple_cmds	*create_cmd_node(char **command, t_lexer **redirections)
{
	t_simple_cmds	*node;

	node = malloc(sizeof(t_simple_cmds));
	node->cmds = command;
	node->next = NULL;
	node->prev = NULL;
	node->redirections = redirections;
	return (node);
}

void	add_cmd_node(t_simple_cmds **simple_cmds, t_simple_cmds *new_node)
{
	t_simple_cmds	*temp;

	temp = (*simple_cmds);
	if (temp)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
	else
		(*simple_cmds) = new_node;
}
