/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:05:36 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/02 20:54:05 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(char **argv)
{
	char	*path;

	if (argv[1] != NULL)
	{
		ft_printf("pwd: too many arguments\n");
		return (0);
	}
	if (argv[0][3] != '\0')
	{
		ft_printf("zsh: command not found: %s\n", argv[0]);
		return (0);
	}
	else
	{
		path = getcwd(NULL, 0);
		if (path == NULL)
			return (0);
		else
		{
			ft_printf("%s\n", path);
			return (1);
		}
	}
}
