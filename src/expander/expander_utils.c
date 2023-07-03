/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <dreis-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:01:27 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/07/02 18:14:17 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_replace(char *str, char *variable, char *value)
{
	char	*result;
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	*temp4;

	temp = ft_strnstr(str, variable, ft_strlen(str));
	temp3 = ft_substr(str, 0, (ft_strlen(str) - ft_strlen(temp) - 1));
	temp4 = ft_strjoin(temp3, value);
	temp2 = ft_substr(temp, ft_strlen(variable),
			(ft_strlen(temp) - ft_strlen(variable) - 0));
	result = ft_strjoin(temp4, temp2);
	free(temp2);
	free(temp3);
	free(temp4);
	return (result);
}

char	*str_replace_2(char *str, char *variable, char *value)
{
	char	*result;
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	*temp4;

	temp = ft_strnstr(str, variable, ft_strlen(str));
	temp3 = ft_substr(str, 0, (ft_strlen(str) - ft_strlen(temp)));
	temp4 = ft_strjoin(temp3, value);
	temp2 = ft_substr(temp, ft_strlen(variable),
			(ft_strlen(temp) - ft_strlen(variable) - 0));
	result = ft_strjoin(temp4, temp2);
	free(temp2);
	free(temp3);
	free(temp4);
	return (result);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
