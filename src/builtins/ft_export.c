/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <dmanuel-@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:49:20 by dmanuel-          #+#    #+#             */
/*   Updated: 2023/05/19 15:07:18 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_exist(t_data *data, char *str)
{

}

int	parameter(char *str)
{

}

char	**add_var(char **arr, char *str)
{

}

void	ft_export(t_data *data, t_simple_cmds *simple_cmds)
{
	char	**temp;
	int		i;

	i = 1;
	if (!simple_cmds->cmds[1] || simple_cmds->cmds[1][0] == '\0')
		ft_env(data);
	else
	{
		while (simple_cmds->cmds[i])
		{
			if (parameter(simple_cmds->cmds[i]) == 0 && var_exist(data, \
				simple_cmds->cmds[i]) == 0)
			{
				if (simple_cmds->cmds[i])
				{
					temp = add_var(data->env, simple_cmds->cmds[i]);
					//free_arr(data->env);
					data->env = temp;
				}
			}
			i++;
		}
	}
}
