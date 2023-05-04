/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreis-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:50:22 by dreis-ma          #+#    #+#             */
/*   Updated: 2023/05/02 20:39:58 by dreis-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;
	char	**input;

	while (1)
	{
		prompt = readline("Minishell$ ");
		if (*prompt)
			add_history(prompt);
		input = ft_split(prompt, ' ');
		if (ft_strncmp("pwd", input[0], 3) == 0)
			pwd(input);
	}
}
