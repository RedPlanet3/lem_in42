/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heula <heula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 22:54:42 by heula             #+#    #+#             */
/*   Updated: 2021/04/14 21:05:38 by heula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void print_lst(t_step **lst)
{
	t_step *back = *lst;
	while (back)
	{
		printf("room: %d, prev_room: %d, old_ch: %c\n", back->room, back->prev_room, back->old_ch);
		back = back->next;
	}
	
}

void	ft_lst_del_back_pn(t_step **lst)
{
	t_step	*back;
	t_step *tmp = *lst;

	

	if (tmp->next != NULL)
	{	
		while (tmp->next->next)
			tmp = tmp->next->next;
		back = ft_lstlast_pn(tmp);
		printf("del %d\n", back->room);
		if (back)
			free(back);
		tmp->next = NULL;
	}
}
