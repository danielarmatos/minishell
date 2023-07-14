/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <dmanuel-@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:06:50 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/07/03 12:16:52 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_error(t_simple_cmds *simple_cmd)
{
	int	i;

	i = 0;
	if (!simple_cmd->cmds[1])
	{
		return (EXIT_SUCCESS);
	}
	while (simple_cmd->cmds[1][i])
	{
		if (simple_cmd->cmds[1][i++] == '/')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(simple_cmd->cmds[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	if (equals(simple_cmd->cmds[1]) != 0)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	export_error(char *c)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (c)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(c, STDERR_FILENO);
		ft_putstr_fd("\': is ", STDERR_FILENO);
	}
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	error_status2(t_data *data, int error, char *string)
{
	if (error == 3)
	{
		printf("%s", "Minishell: ");
		printf("%s", string);
		printf("%s", ": not a valid identifier\n");
		data->exit_status = 1;
	}
	else if (error == 4)
	{
		printf("%s", "Minishell: ");
		printf("%s", string);
		printf("%s", ": numeric argument required\n");
		data->exit_status = 2;
	}
	else if (error == 5)
	{
		printf("%s", "Error: syntax error near unexpected token `");
		printf("%s %s", string, "\n");
		data->exit_status = 2;
	}
	return (data->exit_status);
}

int	error_status(t_data *data, int error, char *string)
{
	if (error == 0)
	{
		printf("%s", "Error: ");
		if (string)
			printf("%s", string);
		perror(" \b");
		data->exit_status = 1;
	}
	else if (error == 1)
	{
		printf("%s", "Minishell: ");
		printf("%s", string);
		printf("%s", ": not enough arguments\n");
		data->exit_status = 1;
	}
	else if (error == 2)
	{
		printf("%s", "Minishell: ");
		printf("%s", string);
		printf("%s", ": too many arguments\n");
		data->exit_status = 1;
	}
	return (error_status2(data, error, string));
}
