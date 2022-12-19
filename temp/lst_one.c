#include "../includes/lem_in.h"

void	ft_lst_add_back_one(t_fin_ways **lst, t_fin_ways *new)
{
	t_fin_ways	*back;

	if (*lst != NULL)
	{
		back = ft_lstlast_one(*lst);
		back->next = new;
	}
	else
		*lst = new;
}

void	ft_lstclear_one(t_fin_ways **lst)
{
	t_fin_ways	*buf;

	while (*lst)
	{
		buf = *lst;
		*lst = (*lst)->next;
        ft_lstclear_pn(buf->step_pointers);
		free(buf);
	}
}

t_fin_ways	*ft_lstnew_one(t_step	**steps)
{
	t_fin_ways	*new;

	new = (t_fin_ways *)ft_malloc(sizeof(t_fin_ways));
    new->step_pointers = steps;
	new->next = NULL;
	return (new);
}

t_fin_ways	*ft_lstlast_one(t_fin_ways *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	else
		return (0);
	return (lst);
}
