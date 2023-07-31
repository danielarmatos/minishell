/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:08:01 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/30 19:43:52 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_file(t_data *data)
{
	data->prompt = ft_strjoin("rm ", "temp_file");
	if (lexical_analysis(data, data->prompt) == 1)
		if (data->lexer[0])
			executor(data, data->simple_cmds[0]);
}

void	execute_here_doc_2(t_data *data, int fd)
{
	set_signals(0);
	close(fd);
	fd = open("temp_file", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	remove_file(data);
}
