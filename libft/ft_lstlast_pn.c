/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heula <heula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 22:41:06 by heula             #+#    #+#             */
/*   Updated: 2021/04/14 21:03:24 by heula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_step	*ft_lstlast_pn(t_step *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	else
		return (0);
	return (lst);
}
