/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <dmanuel-@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:38:48 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/05/04 16:02:16 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	ft_cd(t_data *data, char **argv)
{
	char	*path;

	(void)data;
	if (argv[2] != NULL)
		ft_printf("cd: too many arguments\n");
	path = argv[1];
	if (!path)
		ft_printf("cd: no path\n");
	if (chdir(path) != 0)
		ft_printf("cd: no path\n");
}
