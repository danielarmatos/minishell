/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:08:01 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/01 20:08:07 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_redirection_error(t_lexer *redirections)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(redirections->str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_status = 1;
	return (0);
}

void	remove_file(t_data *data)
{
	data->prompt = ft_strjoin("rm ", "temp_file");
	if (lexical_analysis(data, data->prompt) == 1)
		if (data->lexer[0])
			executor(data, data->simple_cmds[0]);
}

void	execute_here_doc_2(t_data *data, int fd)
{
	(void) data;
	set_signals(0);
	close(fd);
	fd = open("temp_file", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink("temp_file");
}
