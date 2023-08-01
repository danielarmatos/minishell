/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:17:09 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/01 14:00:36 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lexer(t_data *data)
{
	int		len;
	int		i;
	t_lexer	*node;

	i = 0;
	len = 0;
	if (data->lexer)
	{
		if (data->lexer[0])
			len = get_lexer_len(data->lexer[0]);
		while (i < len)
		{
			node = data->lexer[0];
			if (node->str != NULL)
				free(node->str);
			if (node->next)
				data->lexer[0] = data->lexer[0]->next;
			free(node);
			i++;
		}
		free(data->lexer);
	}
	data->lexer = NULL;
}

void	free_simple_cmds(t_data *data)
{
	int				i;
	int				len;
	t_simple_cmds	*node;

	i = 0;
	len = 0;
	if (data->simple_cmds && data->simple_cmds[0])
		len = count_pipes(data->simple_cmds[0]);
	while (i < len)
	{
		node = data->simple_cmds[0];
		free(node->cmds);
		free_redirections(node);
		if (node->next)
			data->simple_cmds[0] = data->simple_cmds[0]->next;
		free (node);
		i++;
	}
	free(data->simple_cmds);
	data->simple_cmds = NULL;
}

void	free_data(t_data *data)
{
	free(data->prompt);
	free(data->pwd);
	free(data->oldpwd);
	data->prompt = NULL;
	data->pwd = NULL;
	data->oldpwd = NULL;
	free_lexer(data);
	free_simple_cmds(data);
	free(data);
	rl_clear_history();
	clear_history();
}

void	ft_exit(t_data *data, t_simple_cmds *simple_cmd)
{
	if (simple_cmd->cmds && simple_cmd->cmds[0][4] != '\0')
	{
		g_exit_status = 1;
		ft_printf("minishell: command not found: %s\n", simple_cmd->cmds[0]);
	}
	else
	{
		if (data->env)
			free_arr(data->env);
		ft_printf("exit\n");
		if (simple_cmd->cmds[1] && digits_only(simple_cmd->cmds[1]) == 1)
			g_exit_status = ft_atoi(simple_cmd->cmds[1]);
		else if (simple_cmd->cmds[1] && digits_only(simple_cmd->cmds[1]) == 0)
		{
			ft_printf("exit: numeric argument required\n");
			g_exit_status = 2;
		}
		free_data(data);
	}
	exit(g_exit_status);
}

void	close_minishell(t_data *data)
{
	int	i;

	i = 0;
	free(data->prompt);
	free(data->pwd);
	free(data->oldpwd);
	if (data->env)
	{
		while (data->env[i])
		{
			free(data->env[i]);
			i++;
		}
		free(data->env);
	}
	if (data->simple_cmds)
		free_simple_cmds(data);
	free(data);
	ft_printf("exit\n");
	rl_clear_history();
	exit(g_exit_status);
}
