/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:41:43 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/18 10:29:21 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int add_simple_cmd(t_data *data, int i, int j)
{
	t_simple_cmds **simple_cmds;

	simple_cmds = malloc(sizeof(t_simple_cmds));
	if (!simple_cmds)
		return (0);
	(*simple_cmds) = 0;
	data->simple_cmds = simple_cmds;
	while (i <= j)
	{
		i++;
	}
	return (0);
}

int check_pipes(t_data *data)
{
	t_lexer	*node;
	int 	i;

	node = data->lexer[0];
	i = 0;
	while (node->next != NULL)
	{
		if (node->token != NULL && node->token[0] == '|')
		{
			add_simple_cmd(data, i, node->index);
		}
		node = node->next;
	}
	if (i == -1)
		i = node->index;
	ft_printf("index: %i\n", i);
	return (i);
}

int parsing(t_data *data)
{
	check_pipes(data);
	return(0);
}