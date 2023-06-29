/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:12:10 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/28 19:25:12 by dreis-ma         ###   ########.fr       */
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
# include <sys/wait.h>

typedef struct s_lexer
{
	int				index;
	char			*str;
	char			*token;
	char			quote_type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}		t_lexer;

typedef struct s_simple_cmds
{
	char					**cmds;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
	t_lexer					**redirections;
}		t_simple_cmds;

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

int				ft_pwd(t_data *data);
int				ft_cd(t_data *data, t_simple_cmds *simple_cmd);
void			ft_exit(t_data *data, t_simple_cmds *simple_cmds);
void			ft_echo(t_data *data, t_simple_cmds *simple_cmd);
int				ft_env(t_data *data);
int				ft_unset(t_data *data, t_simple_cmds *simple_cmds);
int				ft_export(t_data *data, t_simple_cmds *simple_cmds);
void			set_signals(void);
int				executor(t_data *data, t_simple_cmds *cmd);
int				find_pwd(t_data *data);
int				check_identifier(char c);

int				unset_error(t_simple_cmds *simple_cmd);
int				export_error(char *c);
int				env_count(t_data *data);
void			export_env(t_data *data);

int				lexical_analysis(t_data *data);
int				get_lexer_len(t_lexer *lexer);
void			print_lexer(t_data *data);
int				check_quote(char *input, int i);
int				check_single_quote(char *input, int i);
void			add_node(t_lexer **lexer, t_lexer *new_node);
t_lexer			*create_token_node(char *str);
t_lexer			*create_str_node(char *str, char quote_type);
size_t			equals(char *str);

int				parsing(t_data *data);
t_simple_cmds	*create_cmd_node(char **command, t_lexer **redirections);
void			add_cmd_node(t_simple_cmds **simple_cmds, \
							t_simple_cmds *new_node);
char			*delete_quotes(char *str, char c);
void			free_arr(char **split_arr);

void			ft_pipes(t_data *data, t_simple_cmds *simple_cmds);
void			close_pipes(int **pipe_fd, int id);
int				count_pipes(t_simple_cmds *simple_cmds);
int				execute_path(char *name, t_simple_cmds *simple_cmds);
void			execute_direct_path(t_data *data, t_simple_cmds *simple_cmds);
int				check_executable(t_data *data, t_simple_cmds *simple_cmds);
int				check_builtins(t_data *data, t_simple_cmds *simple_cmd);
int				check_invalid_prompt(t_lexer *lexer);
int				check_lexer(t_data *data);

void			close_minishell(t_data *data);
void			free_lexer(t_data *data);
void			free_simple_cmds(t_data *data);
void			clear_data(t_data *data);

//void			expander(t_data *data, t_simple_cmds *simple_cmds);
void			expander(t_data *data, t_lexer *node);
char			*find_variable(t_data *data, char *value);
char			*expand_str(t_data *data, char *str);
void			add_redirections(t_lexer *node, t_lexer **redirections);
int				execute_redirection(t_data *data, t_lexer *redirections);
char			*d_quotes_expander(t_data *data, char *input, int i, int j);
char			*str_replace(char *str, char *variable, char *value);
char			*str_replace_2(char *str, char *variable, char *value);

void			ft_exit_fork(t_data *data);
void			free_data(t_data *data);
void			free_redirections(t_simple_cmds *simple_cmd);

#endif
