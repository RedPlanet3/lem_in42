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
#include "../includes/lem_in.h"

void print_lst(t_step **lst)
{
	t_step *back = *lst;
	while (back)
	{
		printf("%s ", g_vars.list_room[back->room]->name);
		// printf("room: %s, prev_room: %s, old_ch: %c\n", g_vars.list_room[back->room]->name, g_vars.list_room[back->prev_room]->name, back->old_ch);
		back = back->next;
	}
	printf("\n");
	
}

void	ft_lst_del_back_pn(t_step **lst)
{
	t_step	*back = *lst;
	t_step *tmp = *lst;

	if (tmp->next != NULL)
	{
		while (tmp->next->next != NULL)
			tmp = tmp->next;
		back = tmp->next;
		
		// printf("DEL %s", g_vars.list_room[back->room]->name);
		// print_lst(lst);
		if (back)
			free(back);
		tmp->next = NULL;
	}
}
