/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:05:36 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/18 12:53:40 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_pwd(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PWD=", 4))
			data->pwd = ft_substr(data->env[i], 4, ft_strlen(data->env[i]) - 4);
		if (!ft_strncmp(data->env[i], "OLDPWD=", 7))
			data->oldpwd = ft_substr(data->env[i], 7, \
			ft_strlen(data->env[i]) - 7);
		i++;
	}
	return (1);
}

int	ft_pwd(t_data *data, t_simple_cmds *simple_cmd)
{
	(void)simple_cmd;
	ft_putendl_fd(data->pwd, STDOUT_FILENO);
	return (0);
}
