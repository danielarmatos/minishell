/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:41:43 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/15 17:30:10 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_simple_cmd(t_lexer *node, t_data *data, int i, int j)
{
	int		size;
	char	**command;
	int		x;
	t_lexer	**redirections;

	redirections = malloc(sizeof(t_lexer));
	if (!redirections)
		return (0);
	(*redirections) = 0;
	size = j - i + 2;
	command = malloc(sizeof(char *) * size);
	if (!command)
		return (0);
	x = 0;
	while ((i + x) <= j)
	{
		if (node->str == NULL)
		{
			add_redirections(node, redirections);
			i = i + 2;
			if (node->next != NULL)
				node = node->next;
		}
		else
		{
			command[x] = node->str;
			x++;
		}
		node = node->next;
	}
	command[x] = NULL;
	add_cmd_node(data->simple_cmds, create_cmd_node(command, redirections));
	return (0);
}

int	check_pipes(t_data *data)
{
	t_lexer	*node;
	t_lexer	*temp;
	int		i;

	node = data->lexer[0];
	temp = node;
	i = 0;
	while (node->next != NULL)
	{
		if (node->token != NULL && node->token[0] == '|')
		{
			add_simple_cmd(temp, data, i, (node->index - 1));
			i = node->index + 1;
			temp = node->next;
		}
		node = node->next;
	}
	add_simple_cmd(temp, data, i, (node->index));
	return (i);
}

void	print_simple_cmds(t_data *data)
{
	t_simple_cmds	*node;
	int				i;

	node = data->simple_cmds[0];
	ft_printf("\033[0;36mSimple commands:\n\033[0m");
	while (node->next != NULL)
	{
		i = 0;
		while (node->cmds[i])
		{
			ft_printf("%s\n", node->cmds[i]);
			i++;
		}
		i = 0;
	/*	while (node->redirections[0] != NULL)
		{
			ft_printf("Redirection: %s * %s\n", node->redirections[0]->token, node->redirections[0]->str);
			node->redirections[0] = node->redirections[0]->next;
		}*/
		node = node->next;
		ft_printf("\033[0;36m|\n\033[0m");
	}
	i = 0;
	while (node->cmds[i])
	{
		ft_printf("%s\n", node->cmds[i]);
		i++;
	}
}

int	parsing(t_data *data)
{
	t_simple_cmds	**simple_cmds;

	simple_cmds = malloc(sizeof(t_simple_cmds));
	if (!simple_cmds)
		return (0);
	(*simple_cmds) = 0;
	data->simple_cmds = simple_cmds;
	check_pipes(data);
	//print_simple_cmds(data);
	return (0);
}
