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


void	ft_lst_del_back_pn(t_step **lst)
{
	t_step	*back;

	if (*lst != NULL)
	{
		back = ft_lstlast_pn(*lst);
		free(back);
		back = NULL;
	}
}
