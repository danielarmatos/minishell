/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:12:10 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/18 12:53:40 by dmanuel-         ###   ########.fr       */
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

typedef struct s_simple_cmds
{
	char					**str;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}		t_simple_cmds;

typedef struct s_lexer
{
	int				index;
	char			*str;
	char			*token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}		t_lexer;

typedef struct s_data
{
	char					**env;
	char					*pwd;
	char					*oldpwd;
	char					*prompt;
	int						exit_status;
	struct s_lexer			**lexer;
	struct s_simple_cmds	**simple_cmds;
}		t_data;

int		ft_pwd(t_data *data, t_simple_cmds *simple_cmd);
void	ft_cd(t_data *data, t_simple_cmds *simple_cmd);
void	ft_exit(t_data *data, char **input);
void	ft_echo(t_data *data, char **argv);
int		ft_env(t_data *data);
void	set_signals(void);
int		check_executable(t_data *data, char **input);
int		find_pwd(t_data *data);

int		lexical_analysis(t_data *data);
int		check_quote(char *input, int i);
void	add_node(t_lexer **lexer, t_lexer *new_node);
t_lexer	*create_token_node(char *str);
t_lexer	*create_str_node(char *str);

int		parsing(t_data *data);

#endif
