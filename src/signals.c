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

/*void	set_signals(t_data *data, int i)
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
}*/

void	set_signals(t_data *data, int i)
{
	struct sigaction	signal;

	if (i == 0)
		signal.sa_sigaction = &handle_signals;
	else
		signal.sa_sigaction = &handle_signals_2;
	signal.sa_flags = SA_SIGINFO;
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = SA_SIGINFO;
	signal.sa_sigaction = &handle_signals;
	signal.sa_mask = signal.sa_mask;
	signal.sa_flags |= SA_SIGINFO;
	signal.sa_restorer = NULL;
	signal.sa_sigaction = &handle_signals;

	// Pass the address of myData to the signal handler via si_value
	signal.sa_sigaction = &handle_signals;
	sigemptyset(&signal.sa_mask);
	sigaddset(&signal.sa_mask, SIGINT);
	sigaddset(&signal.sa_mask, SIGQUIT);
	signal.sa_flags = SA_SIGINFO;
	signal.sa_sigaction = &handle_signals;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);

	// Rest of your code
	// ...
}