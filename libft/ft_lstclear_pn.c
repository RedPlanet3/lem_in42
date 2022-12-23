/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heula <heula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 19:05:45 by heula             #+#    #+#             */
/*   Updated: 2021/07/18 17:22:02 by heula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_lstclear_pn(t_step **lst)
{
	t_step	*buf;

	while (*lst)
	{
		buf = *lst;
		*lst = (*lst)->next;
		printf("ft_lstclear_pn(t_step **lst)\n");
		free(buf);
	}
}
