/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heula <heula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:13:07 by heula             #+#    #+#             */
/*   Updated: 2021/07/18 17:20:18 by heula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_step	*ft_lstmap_pn(t_step *lst, void *(*f)(void *), void (*del)(void *))
{
	t_step	*newlist;
	t_step	*newelmnt;

	if (!lst)
		return (0);
	newlist = ft_lstnew(f(lst->content));
	if (newlist == NULL)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		newelmnt = ft_lstnew(f(lst->content));
		if (newelmnt == NULL)
			ft_lstclear(&newlist, del);
		else
			ft_lstadd_back(&newlist, newelmnt);
	}
	return (newlist);
}
