/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:02:17 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/13 20:53:07 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_here_doc(t_lexer *redirections)
{
	int		fd;
	char	*str;

	fd = open("temp_file", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		str = readline("> ");
		if (ft_strncmp(str, redirections->str, ft_strlen(redirections->str) + 1) == 0)
			break ;
		ft_putendl_fd(str, fd);
	}
	close(fd);
	fd = open("temp_file", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	remove("temp_file");
}

int	execute_redirection(t_lexer *redirections)
{
	int fd;
	while (redirections)
	{
		if (redirections->token[0] == '>')
		{
			if (redirections->token[0] == '>' && redirections->token[1] == '>')
				fd = open(redirections->str, O_CREAT | O_RDWR | O_APPEND, 0644);
			else
				fd = open(redirections->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (redirections->token[0] == '<')
		{
			if (redirections->token[0] == '<' && redirections->token[1] == '<')
				execute_here_doc(redirections);
			else
			{
				fd = open(redirections->str, O_RDONLY);
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
		}
		redirections = redirections->next;
	}
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