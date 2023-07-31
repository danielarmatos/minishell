/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:37:37 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/30 19:41:04 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_signals_2(t_data *static_data, int sig)
{
	if (sig == SIGINT && static_data->interactive == 1)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		set_signals(0);
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (sig == SIGQUIT && static_data->interactive == 0)
	{
		ft_printf("\b\b  \b\b");
		rl_redisplay();
	}
	else if (sig == SIGQUIT && static_data->interactive == 1)
	{
		ft_printf("\b\b  \b\b");
		rl_redisplay();
		ft_printf("^\\Quit (core dumped)\n");
	}
}
