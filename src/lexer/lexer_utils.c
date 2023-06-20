/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:54:37 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/20 19:24:08 by dreis-ma         ###   ########.fr       */
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

t_lexer	*create_str_node(char *str, char quote_type)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	node->index = 0;
	node->str = str;
	node->token = NULL;
	node->next = NULL;
	node->prev = NULL;
	node->quote_type = quote_type;
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
