/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:02:17 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/08 16:54:22 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_here_doc(t_data *data, t_lexer *redir)
{
	int		fd;
	char	*str;

	data->interactive = 0;
	set_signals(1);
	handle_heredoc_signals(0, data);
	fd = open("temp_file", O_CREAT | O_RDWR | O_TRUNC, 0644);
	data->fd = fd;
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			ft_printf("\b\b  \b\b");
			break ;
		}
		if (ft_strncmp(str, redir->str, ft_strlen(redir->str) + 1) == 0)
			break ;
		while (ft_strchr(str, '$') != 0)
			str = expander(data, str, 0);
		ft_putendl_fd(str, fd);
		free(str);
		str = NULL;
	}
	execute_here_doc_2(data, fd);
}

int	redirect_input(t_data *data, t_lexer *redirections)
{
	int	fd;

	if (redirections->token[0] == '<' && redirections->token[1] == '<')
	{
		dup2(data->og_ioput[0], STDIN_FILENO);
		execute_here_doc(data, redirections);
	}
	else
	{
		fd = open(redirections->str, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redirections->str, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_exit_status = 1;
			return (0);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (1);
}

int	execute_redirection(t_data *data, t_lexer *redirections, int fd)
{
	while (redirections)
	{
		if (redirections->token[0] == '>')
		{
			if (redirections->token[0] == '>' && redirections->token[1] == '>')
			{
				fd = open(redirections->str, O_CREAT | O_RDWR | O_APPEND, 0644);
				if (fd == -1)
					return (execute_redirection_error(redirections));
			}
			else
			{
				fd = open(redirections->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
				if (fd == -1)
					return (execute_redirection_error(redirections));
			}
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
