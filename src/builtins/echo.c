/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <dmanuel-@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:04:33 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/05/11 21:00:37 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_data *data, char **argv)
{
	int	i;
	int	n;

	(void)data;
	i = 1;
	n = 0;
	if (argv[1] && ft_strncmp(argv[1], "-n", 3) == 0)
	{
		n = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
