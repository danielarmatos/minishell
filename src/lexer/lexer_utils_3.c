/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:15:25 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/08/02 21:20:10 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*count_quotes_3(char *str)
{
	free(str);
	return (0);
}

char	count_quotes_2(t_data *data)
{
	data->quote_count++;
	return ('n');
}

void	clean_string_vars(t_data *data)
{
	data->quote_count = 0;
	data->quote_type = 'n';
}
