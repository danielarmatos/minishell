/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:57:06 by dmanuel-          #+#    #+#             */
/*   Updated: 2022/11/15 11:50:46 by dmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*info;

	if (!lst)
		return (0);
	new = 0;
	while (lst)
	{
		info = ft_lstnew(f(lst->content));
		if (!info)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, info);
		lst = lst->next;
	}
	return (new);
}
