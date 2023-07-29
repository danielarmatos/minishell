/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:41:53 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/29 16:54:02 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    SIGINT - ctrl-C displays a new prompt on a new line.
    SIGQUIT - ctrl-\ does nothing
*/

static void	handle_signals(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
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

static void	handle_interactive_signals(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
		ft_printf("\n");
	else if (sig == SIGQUIT)
	{
		ft_printf("\b\b  \b\b");
		rl_redisplay();
		ft_printf("^\\Quit (core dumped)\n");
	}
}

void	handle_heredoc_signals(int sig, void *data)
{
	static t_data	*static_data;

	if (!static_data && data)
		static_data = (t_data *)data;
	if (static_data)
	{
		if (sig == SIGINT && static_data->interactive == 0)
		{
			ft_printf("\n");
			set_signals(0);
			close(static_data->fd);
			static_data->fd = open("temp_file", O_RDONLY);
			dup2(static_data->fd, STDIN_FILENO);
			close(static_data->fd);
			remove("temp_file");
			exit_status = 130;
			rl_redisplay();
			rl_redisplay();
			ft_printf("\b\b\b\b\b\b\b\b\b\b\b           \b\b\b\b\b\b\b\b\b\b\b\b");
			ft_exit_fork(static_data);
		}
		else if (sig == SIGINT && static_data->interactive == 1)
		{
			ft_printf("\n");
			rl_replace_line("", 0);
			set_signals(0);
			rl_redisplay();
			exit_status = 130;
		}
		else if (sig == SIGQUIT)
		{
			ft_printf("\b\b  \b\b");
			rl_redisplay();
		}
	}
}

static void	handle(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	handle_heredoc_signals(sig, 0);
}

void set_signals(int i)
{
	struct sigaction signal;

	signal.sa_flags = SA_SIGINFO;
	sigemptyset(&signal.sa_mask);
	if (i == 0)
		signal.sa_sigaction = &handle_signals;
	else if (i == 1)
		signal.sa_sigaction = &handle;
	else if (i == 2)
		signal.sa_sigaction = &handle_interactive_signals;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}
