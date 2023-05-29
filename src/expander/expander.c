/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:53:39 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/28 19:14:58 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_str(t_simple_cmds *simple_cmds, int i)
{
	ft_printf("expander: %s\n", simple_cmds->cmds[i]);
}

void	expander(t_simple_cmds *simple_cmds)
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
				expand_str(node, j);
			j++;
		}
		if (node->next)
			node = node->next;
		i++;
	}
}
