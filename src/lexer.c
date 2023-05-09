/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:00:11 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/09 21:16:45 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int add_token(t_data *data, char *input, int i)
{

	return (0);
}

int	lexical_analysis(t_data *data)
{
	//(void)data;
	t_lexer	**lexer;
	int 	i;
	char 	*input;
	char 	*str;

	input = data->prompt;
	i = 0;
	lexer = malloc(sizeof(t_lexer *));
	if (!lexer)
		return (0);
	(*lexer) = 0;
	/*while (input[i])
	{
		ft_printf("%s\n", input[i]);
		if (input[i][0] == '|' && input[i][1] == '\0')
		{
			ft_printf("pipe\n");
		}

		//if (input[i][0] == '|' || input[i][0] == '<' | input[i][0] == '>')
		i++;
	}*/
	while (input[i])
	{
		while (input[i] >= 9 && input[i] <= 13)
			i++;
		if (input[i] == '|' || input[i] == '<' | input[i] == '>')
			add_token(data, input, i);

	}
	return (1);
}