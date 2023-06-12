/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:02:17 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/12 20:21:43 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_redirection(t_lexer *redirections)
{
	FILE *file;
	int fd;
	file = fopen(redirections->str, "w");
	fd = open(redirections->str, O_WRONLY);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

t_lexer	*create_redirection_node(char *str, char *token)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	node->index = 0;
	node->str = str;
	node->token = token;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_redirections(t_lexer *node, t_lexer **redirections)
{
	char *str;

	if (node->next->str)
		str = node->next->str;
	else
		str = NULL;
	add_node(redirections, create_redirection_node(str, node->token));
}