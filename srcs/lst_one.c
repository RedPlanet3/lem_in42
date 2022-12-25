#include "../includes/lem_in.h"

void	ft_lstclear_one(t_fin_ways **lst)
{
	t_fin_ways	*buf;

	while (*lst)
	{
		buf = *lst;
		*lst = (*lst)->next;

        free(buf->step_index);
		free(buf);
	}
}

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

int	ft_lstsize_one(t_fin_ways *lst)
{
	t_fin_ways	*move;
	int		size;

	size = 1;
	move = lst;
	if (!lst)
		return (0);
	while (move->next != NULL)
	{
		size++;
		move = move->next;
	}
	return (size);
}

int* full_arr_int(t_step *lst, int size)
{
    int *arr = (int*)ft_malloc(size * sizeof(int));
    int ch = 0;
	if (!lst)
		return NULL;
	while (lst->next != NULL)
	{
        arr[ch] = lst->room;
		lst = lst->next;
        ch++;
	}
    arr[ch] = lst->room;

	// printf("                     WAY: ");
	// for(int i=0; i<size;i++)
	// 	printf("%s ",g_vars.list_room[arr[i]]->name);
	// printf("\n");
    return arr;
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

t_fin_ways	*ft_lstnew_one(t_step	**steps)
{
	t_fin_ways	*new;

	new = (t_fin_ways *)ft_malloc(sizeof(t_fin_ways));
    new->length_way = ft_lstsize_pn(*steps);
    new->step_index = full_arr_int(*steps, new->length_way);
	new->next = NULL;
	return (new);
}

void print_ways(t_fin_ways **g_fin_ways)
{
	printf("\nprint_ways: %d:\n", g_vars.number_of_ways);
	t_fin_ways *ways = *g_fin_ways;
	while (ways)
	{
		printf("\n");
		for (int i = 0; i < ways->length_way; i++)
		{
			printf("%s\t", g_vars.list_room[ways->step_index[i]]->name);
			// write(1, g_vars.list_room[ways->step_index[i]]->name, ft_strlen(g_vars.list_room[ways->step_index[i]]->name));
		}
		printf("\n");
		ways = ways->next;
	}
}


