#include "../includes/lem_in.h"

int count;

// Проверка на использованные кормнаты в пути и на возврат в старт
// 0 - связь использовать нельзя
int check_connection(int dest) 
{
    // printf("%s heck_connection: '%c' ", g_vars.list_room[dest]->name, g_cur_rooms[dest]);
    if(dest == 0)
    {
        // printf("return 0\n");
        return 0;
    }
    else if (g_cur_rooms[dest] == ' ')
    {
        // printf("return 1\n");
        return 1;
    }
    else
    {
        // printf("return 0\n");
        return 0;
    }
}

void create_matrix(unsigned int number_of_rooms)
{
    g_sm_matrix = (char**)malloc(number_of_rooms * sizeof(char*));
    for (unsigned int i = 0; i<number_of_rooms; i++)
    {
        g_sm_matrix[i] = (char*)malloc(number_of_rooms * sizeof(char));
        for (unsigned int j = 0; j<number_of_rooms; j++)
        {
            g_sm_matrix[i][j] = ' ';
        }
    }
}

void g_cur_rooms_create(unsigned int number_of_rooms, int create)
{
    if (create)
        g_cur_rooms = (char*)malloc(number_of_rooms * sizeof(char));
    for (unsigned int j = 0; j < number_of_rooms; j++)
        g_cur_rooms[j] = ' ';
}

void full_matrix(int i, int j, char a, char b)
{
    g_sm_matrix[i][j] = a;
    g_sm_matrix[j][i] = b;
}

int find_ch(int room, int start, char c)
{
    for (unsigned int j = start; j < g_vars.number_of_rooms; j++)
    {
        if (g_sm_matrix[room][j] == c)
            return j;
    }
    return -1;
}

int finish_check(int prew, int room)
{
    // printf("finish_check(%s, %s)", g_vars.list_room[prew]->name, g_vars.list_room[room]->name);
    (void)prew;
    for(unsigned int i = 0; i < g_vars.list_room[room]->number_of_conn; i++)
    {
        if (g_vars.list_room[room]->conn_pointers[i]->index == (int)g_vars.number_of_rooms - 1)        
        {
            if (find_ch(room, 0, '+') != -1)
            {
                // printf("\tno\n");
                return 0;
            }
            else
            {
                // printf("\tyes\n");
                return 1;
            }
        }
    }
    // printf("\tno\n");
    return 0;
}

void rollback(int prew, int room)
{
    if (g_cur_rooms[room] != '-')
    {    
        // printf("del: %s\n", g_vars.list_room[room]->name);
        if (g_sm_matrix[prew][room] == '+')
            full_matrix(prew, room, ' ', ' ');

        else if (g_sm_matrix[prew][room] == ' ')
            full_matrix(prew, room, '-', '+');

        g_cur_rooms[room] = '-';
    }
}

int room_check(int prew, int room)
{
    // printf("room_check(%s, %s)", g_vars.list_room[prew]->name, g_vars.list_room[room]->name);
    if (check_connection(room))           // проверяем, можем ли мы использовать эту связь
    {
        // printf("\tok!\n");
        // printf("room_check add: %s\n", g_vars.list_room[room]->name);
        g_cur_rooms[room] = '+';
        if (g_sm_matrix[prew][room] == '-')
            full_matrix(prew, room, ' ', ' ');
        else if (g_sm_matrix[prew][room] == ' ')
            full_matrix(prew, room, '+', '-');
        return(full_current_step(prew, room));     //может возвращать
    }
    // printf("\tno!\n");
    return -3;
}

int find_minus(int prew, int room)
{
    int ch = 0;
    int a;
    
    while (ch != -1)
    {
        // printf("find_minus(%s, %s)", g_vars.list_room[prew]->name, g_vars.list_room[room]->name);
        ch = find_ch(room, ch, '-');
        if (ch == -1)
            continue;
        // printf("\tyes\n");
        a = room_check(room, ch);
        if (a == -1)
            return -1;
        else if (a == -2)
            rollback(room, ch);
        ch = find_ch(room, ch + 1, '-');
    }
    // printf("\tno\n");
    rollback(prew, room);
    return -2; // не найдена следующая комната
}

int full_current_step(int prew, int room)
{
    // printf("full_current_step(%s, %s)\n", g_vars.list_room[prew]->name, g_vars.list_room[room]->name);
    int a;
    if (room == 0)
    {
        rollback(prew, room);
        return -2;
    }

    if (finish_check(prew, room) || room == (int)g_vars.number_of_rooms - 1)
    {
        if (room != (int)g_vars.number_of_rooms - 1)
        {   
            g_cur_rooms[g_vars.number_of_rooms - 1] = '+';
            // printf("full_current_step, finish_check, add: %s\n", g_vars.list_room[g_vars.number_of_rooms - 1]->name);
            full_matrix(room, g_vars.number_of_rooms - 1, '+', ' '); //в матрице отображаем наш ход
        }
        g_vars.number_of_ways++; //увеличиваю поличество путей
        return -1; //код завершения
    }
    
    if (room != 0 && find_ch(room, 0,'+') != -1)
        return find_minus(prew, room);
    else
    {    
        for (unsigned int i = 0; i < g_vars.list_room[room]->number_of_conn; i++)
        {
            a = room_check(room, g_vars.list_room[room]->conn_pointers[i]->index);
            if (a == -2)
                continue;
            if (a == -1)
                return -1;
        }
    }
    rollback(prew, room);
    return -2;
}

void finish_ways()
{
    int room;

    room = find_ch(0, 0, '+');
    while (room != -1)
    {
        ft_lst_add_back_pn(&g_steps, ft_lstnew_pn(0,' ', 0));
        
        if (room != -1)
            g_sm_matrix[0][room] = ' ';
        while (room != -1)
        {
            ft_lst_add_back_pn(&g_steps, ft_lstnew_pn(room,' ', 0));
            // printf("room %s search '+' and find in ", g_vars.list_room[room]->name);
            room = find_ch(room, 0, '+');
            // printf("%s\n", g_vars.list_room[room]->name);
        }
        ft_lst_add_back_one(&g_fin_ways, ft_lstnew_one(&g_steps));
        ft_lstclear_pn(&g_steps);
        room = find_ch(0, 0, '+');
    }
}

void clean_matrix()
{
    for (unsigned int i = 0; i < g_vars.number_of_rooms; i++)
    {
        free(g_sm_matrix[i]);
    }
    free(g_sm_matrix);
    free(g_cur_rooms);
}

void alg()
{
    // printf("start alg\n");
    int a;
    g_vars.number_of_ways = 0;
    
    for(unsigned int i = 0; i < g_vars.number_of_rooms; i++)
        g_vars.list_room[i]->index = i;

    create_matrix(g_vars.number_of_rooms); // ее потом нужно будет очистить по завершени/ю алгоритма
    g_cur_rooms_create(g_vars.number_of_rooms, 1);
    for (unsigned int i = 0; i < g_vars.list_room[0]->number_of_conn; i++)
    {
        // printf("0 to %s\n", g_vars.list_room[0]->conn_pointers[i]->name); /////
        g_cur_rooms[0] = '+';
        // printf("alg, 0, add: %s\n", g_vars.list_room[0]->name);
        g_cur_rooms[g_vars.list_room[0]->conn_pointers[i]->index] = '+';
        // printf("alg, 1, add: %s\n", g_vars.list_room[0]->conn_pointers[i]->name);
        
        full_matrix(0, g_vars.list_room[0]->conn_pointers[i]->index, '+', ' ');
        
        a = full_current_step(0, g_vars.list_room[0]->conn_pointers[i]->index);
        if (a == -2)
            rollback(0, g_vars.list_room[0]->conn_pointers[i]->index);
        g_cur_rooms_create(g_vars.number_of_rooms, 0);
    }
    // printf("FINISH MATRIX:\n");
    // print_matrix(g_sm_matrix);
    finish_ways();
    clean_matrix();
}