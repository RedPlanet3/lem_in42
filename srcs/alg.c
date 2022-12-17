#include "../includes/lem_in.h"
t_step *steps;

void create_matrix(unsigned int number_of_rooms)
{
    sm_matrix = (char**)malloc(number_of_rooms * sizeof(char*));
    for (unsigned int i = 0; i<number_of_rooms; i++)
    {
        sm_matrix[i] = (char*)malloc(number_of_rooms * sizeof(char));
        for (unsigned int j = 0; j<number_of_rooms; j++)
        {
            sm_matrix[i][j] = '';
        }
    }
}

void full_matrix(int i, int j, char a, char b)
{
    sm_matrix[i][j] = a;
    sm_matrix[j][i] = b;
}

int find_ch(int room, int start, char c)
{
    for (unsigned int j = start; j<g_vars.number_of_rooms; j++)
    {
        if (sm_matrix[room][j] == '+')
            return j;
    }
    return -1;
}

void full_current_step(int room)
{
    if (room != 0 && find_ch(room, 0,'+') != -1)
    {
        ch = 0
        while (ch != -1)
        {
            ch = find_ch(room, ch, '-');
            check_connection(room, ch);
        }
    }

    for (i = 0; i < g_vars.list_room[room]->number_of_conn; i++)
    {
        if (check_connection(room, g_vars.list_room[room]->conn_pointers[i]->index))
            break;
        else
            continue;
    }
}

bool check_connection(int i, int dest)
{
    t_step **tmp_steps = *steps;
    while (*tmp_steps->next != NULL)
	{
		if(*tmp_steps->room == dest)
            return 0;
		*tmp_steps = lst->next;
	}
}



void alg()
{
    for(int i; i < g_vars.number_of_rooms; i++)
    {
        g_vars.list_room[i]->index = i;
    }
    ways[i] = (char*)malloc(number_of_rooms * sizeof(char));
    create_matrix(t_vars.number_of_rooms);


    for (i = 0; i < g_vars.list_room[0]->number_of_conn; i++)
    {
        steps = ft_lst_add_back_pn(ft_lstnew_pn(0,''));
        full_current_step(0);


        ft_lst_del_back_pn(steps); // del steps
    }
    ft_lst_del_back_pn(steps); // del steps
    
    while (/* condition */)
    {
        
    }
    

}