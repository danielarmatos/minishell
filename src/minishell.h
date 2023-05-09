/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:12:10 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/09 21:08:51 by dreis-ma         ###   ########.fr       */
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

typedef struct s_lexer
{
	int 			index;
	char 			*str;
	char 			token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}		t_lexer;

int		ft_pwd(t_data *data, char **argv);
void	ft_cd(t_data *data, char **argv);
void	ft_exit(t_data *data, char **input);
void	ft_echo(t_data *data, char **argv);
int		ft_env(t_data *data);
void	set_signals(void);
int		check_executable(t_data *data, char **input);
int		lexical_analysis(t_data *data);
char	**input_split(char const *s, char c);

#endif
