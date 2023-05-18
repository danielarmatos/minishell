/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:54:37 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/15 17:36:35 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote(char *input, int i)
{
	int	quote;

	quote = 0;
	if (input[i] == '\"')
	{
		quote = 1;
		i++;
		while (input[i])
		{
			if (input[i] == '\"')
				quote++;
			i++;
		}
	}
	if (quote % 2 != 0)
		quote--;
	return (quote);
}

t_lexer	*create_token_node(char *str)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	node->index = 0;
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
