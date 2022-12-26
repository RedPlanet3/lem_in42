#include "../includes/lem_in.h"

void print_matrix(char **matrix)
{
    printf("\t");
    for (int i = 0; i < (int)g_vars.number_of_rooms; i++)
    {
        printf("%s\t",g_vars.list_room[i]->name);
    }
    printf("\n");
    for (int i = 0; i < (int)g_vars.number_of_rooms; i++)
    {
        printf("%s\t",g_vars.list_room[i]->name);
        for (int j = 0; j < (int)g_vars.number_of_rooms; j++)
        {
            printf("%c\t",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_rooms(int conn)
{
    for (int i = 0; i < (int)g_vars.number_of_rooms; i++)
    {
        printf("************************************\ncurrent room index: %d, room name: %s \n", g_vars.list_room[i]->index, g_vars.list_room[i]->name);
        if (conn)
        {
            printf("conn_pointers:\n");
            for (int j = 0; j < (int)g_vars.list_room[i]->number_of_conn; j++)
            {
                printf("i: %d, room index: %d, room name: %s \n", i, g_vars.list_room[i]->conn_pointers[j]->index, g_vars.list_room[i]->conn_pointers[j]->name);
            }
        }
    }
    printf("\n");
}

void print_ways(t_fin_ways **g_fin_ways)
{
	printf("\nprint_ways: %d:\n", g_vars.number_of_ways);
	t_fin_ways *ways = *g_fin_ways;
	while (ways)
	{
		printf("\n");
		for (int i = 0; i < ways->length_way; i++)
			printf("%s\t", g_vars.list_room[ways->step_index[i]]->name);
		printf("\n");
		ways = ways->next;
	}
}