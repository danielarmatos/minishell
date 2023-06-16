/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:53:39 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/15 18:50:35 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_str(t_data *data, t_simple_cmds *simple_cmds, int i)
{
	int		j;
	int		found;
	char	**str;
	char 	*variable;

	j = 0;
	found = 0;
	variable = simple_cmds->cmds[i];
	variable++;
	while (data->env[j])
	{
		str = ft_split(data->env[j], '=');
		if (ft_strncmp(variable, str[0], ft_strlen(str[0])) == 0)
		{
			found = 1;
			break ;
		}
		j++;
	}
	if (found == 1)
	{
		//free(simple_cmds->cmds[i]);
		simple_cmds->cmds[i] = str[1];
	}
	free(str[0]);
	/*else
	{
		free(str[0]);
		free(str[1]);
		free(str);
	}*/
}

void	expander(t_data *data, t_simple_cmds *simple_cmds)
{
	int				i;
	int				j;
	int				len;
	t_simple_cmds	*node;

	i = 0;
	j = 0;
	len = 0;
	if (simple_cmds)
		len = count_pipes(simple_cmds);
	node = simple_cmds;
	while (i < len)
	{
		while (node->cmds[j])
		{
			if (node->cmds[j][0] == '$' && node->cmds[j][1])
				expand_str(data, node, j);
			j++;
		}
		if (node->next)
			node = node->next;
		i++;
	}
}
