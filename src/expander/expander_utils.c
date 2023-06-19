/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:01:27 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/06/19 20:37:58 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_replace(char *str, char *variable, char *value)
{
	char	*result;
	char	*temp;
	char	*temp2;

	temp = ft_strnstr(str, variable, ft_strlen(str));
	result = ft_substr(str, 0, (ft_strlen(str) - ft_strlen(temp) - 1));
	result = ft_strjoin(result, value);
	temp2 = ft_substr(temp, ft_strlen(variable),
			(ft_strlen(temp) - ft_strlen(variable) - 1));
	result = ft_strjoin(result, temp2);
	return (result);
}
