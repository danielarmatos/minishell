/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:02:17 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/14 20:03:13 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_here_doc(t_data *data, t_lexer *redirections)
{
	int		fd;
	char	*str;

	fd = open("temp_file", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		str = readline("> ");
		if (ft_strncmp(str, redirections->str,
				ft_strlen(redirections->str) + 1) == 0)
			break ;
		while (ft_strchr(str, '$') != 0)
			str = expander(data, str, 0);
		ft_putendl_fd(str, fd);
	}
	close(fd);
	fd = open("temp_file", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	remove("temp_file");
}

int	redirect_input(t_data *data, t_lexer *redirections)
{
	int	fd;

	if (redirections->token[0] == '<' && redirections->token[1] == '<')
		execute_here_doc(data, redirections);
	else
	{
		fd = open(redirections->str, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("minishell: %s: No such file or directory\n",
				redirections->str);
			exit_status = 1;
			return (0);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (1);
}

int	execute_redirection(t_data *data, t_lexer *redirections)
{
	int	fd;

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
			if (redirect_input(data, redirections) == 0)
				return (0);
		redirections = redirections->next;
	}
	return (1);
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
	char	*str;

	if (node->next->str)
		str = node->next->str;
	else
		str = NULL;
	add_node(redirections, create_redirection_node(str, node->token));
}
