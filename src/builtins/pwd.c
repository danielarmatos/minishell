/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:16:27 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/20 11:05:46 by dmanuel-         ###   ########.fr       */
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

int	ft_pwd(t_data *data)
{
	ft_putendl_fd(data->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
