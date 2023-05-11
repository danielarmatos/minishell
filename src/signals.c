/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:41:53 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/11 20:59:20 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    SIGINT - ctrl-C displays a new prompt on a new line.
    SIGQUIT - ctrl-\ does nothing
*/

static void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\b\b  \b\b");
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_printf("\b\b  \b\b");
		rl_redisplay();
	}
}

void	set_signals(void)
{
	struct sigaction	signal;

	signal.sa_handler = &handle_signals;
	signal.sa_flags = 0;
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}
