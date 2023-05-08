/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:12:10 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/08 12:54:39 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "../libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_data
{
	char	**env;
	char	*prompt;
	int		exit_status;
}		t_data;

int		ft_pwd(t_data *data, char **argv);
void	ft_cd(t_data *data, char **argv);
void	ft_exit(t_data *data, char **input);
void	ft_echo(t_data *data, char **argv);
int		ft_env(t_data *data);
void	set_signals(void);

#endif
