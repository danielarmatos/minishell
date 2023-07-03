/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:54:37 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/01 19:22:05 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_lexer_len(t_lexer *lexer)
{
	t_lexer	*node;
	int		i;

	i = 1;
	node = lexer;
	while (node->next != NULL)
	{
		node = node->next;
		i++;
	}
	return (i);
}

t_lexer	*create_token_node(char *str)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	node->index = 0;
	node->quote_type = 'n';
	node->str = NULL;
	node->token = str;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_lexer	*create_str_node(char *str)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	node->index = 0;
	node->str = str;
	node->token = NULL;
	node->next = NULL;
	node->prev = NULL;
	node->quote_type = 's';
	return (node);
}

void	add_node(t_lexer **lexer, t_lexer *new_node)
{
	t_lexer	*temp;

	temp = (*lexer);
	if (temp)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
		new_node->index = new_node->prev->index + 1;
	}
	else
		(*lexer) = new_node;
}

void	print_lexer(t_data *data)
{
	t_lexer	*node;

	if (!data->lexer[0])
		return ;
	node = data->lexer[0];
	while (node->next != NULL)
	{
		if (node->str != NULL)
			ft_printf("%i: %s\n", node->index, node->str);
		else if (node->token != NULL)
			ft_printf("\033[0;36m%i: %s\033[0m\n", node->index, node->token);
		node = node->next;
	}
	if (node->str != NULL)
		ft_printf("%i: %s\n", node->index, node->str);
	else if (node->token != NULL)
		ft_printf("\033[0;36m%i: %s\033[0m\n", node->index, node->token);
	ft_printf("\n");
}
