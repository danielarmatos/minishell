/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:41:53 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/15 19:48:47 by dreis-ma         ###   ########.fr       */
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
		exit_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_printf("\b\b  \b\b");
		rl_redisplay();
	}
}

//This function is for the ctrl-C inside a <<
static void	handle_signals_2(int sig)
{
	if (sig == SIGINT)
	{
		/*ft_printf("\b\b  \b\b");
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_status = 130;*/
	}
	else if (sig == SIGQUIT)
	{
		ft_printf("\b\b  \b\b");
		rl_redisplay();
	}
}

void	set_signals(int i)
{
	struct sigaction	signal;

	if (i == 0)
		signal.sa_handler = &handle_signals;
	else
		signal.sa_handler = &handle_signals_2;
	signal.sa_flags = 0;
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}
