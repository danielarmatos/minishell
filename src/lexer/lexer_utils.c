/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:54:37 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/11 20:52:39 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	}
	else
		(*lexer) = new_node;
}
