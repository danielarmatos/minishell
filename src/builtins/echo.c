/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <dmanuel-@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:04:33 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/05/24 10:52:43 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_line(int i, char **str, int out)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], out);
		if (str[i])
			ft_putchar_fd(' ', out);
	}
}

void	ft_echo(t_data *data, t_simple_cmds *simple_cmd)
{
	int	i;
	int	n;
	int	j;

	(void)data;
	i = 1;
	n = 0;
	while (simple_cmd->cmds[i] && simple_cmd->cmds[i][0] == '-' && \
			simple_cmd->cmds[i][1] == 'n')
	{
		j = 1;
		while (simple_cmd->cmds[i][j] == 'n')
			j++;
		if (simple_cmd->cmds[i][j] == '\0')
			n = 1;
		else
			break ;
		i++;
	}
	write_line(i, simple_cmd->cmds, STDOUT_FILENO);
	if (n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
