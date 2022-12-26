#include "../includes/lem_in.h"

// t_step **steps;
// char **g_sm_matrix;
int count;


// Проверка на использованные кормнаты в пути и на возврат в старт
// 0 - связь использовать нельзя
int check_connection(int dest) 
{
    if (g_cur_rooms[dest] != -1)
        return 0;
    else
        return 1;
    // t_step *tmp_steps = g_steps;
    
    // while (tmp_steps->next != NULL)
	// {
        
	// 	if(tmp_steps->room == dest)
    //         return 0;
    //     // else if(tmp_steps->room == 0)
    //     //     return 0;
	// 	tmp_steps = tmp_steps->next;
	// }
    // // printf("next room %s\n", g_vars.list_room[dest]->name);
    // // printf("find dest\n");
    // return 1;
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
        g_cur_rooms = (short*)malloc(number_of_rooms * sizeof(short));
    for (unsigned int j = 0; j < number_of_rooms; j++)
        g_cur_rooms[j] = -1;
}

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

void full_matrix(int i, int j, char a, char b)
{
    g_sm_matrix[i][j] = a;
    g_sm_matrix[j][i] = b;
    // print_matrix(g_sm_matrix);
}

int find_ch(int room, int start, char c)
{
    // if (c == '-')
    //     print_matrix(g_sm_matrix);
    for (unsigned int j = start; j < g_vars.number_of_rooms; j++)
    {
        // printf("j: %d\n", j);
        // printf("find next - room %s:j %s\n", g_vars.list_room[room]->name, g_vars.list_room[j]->name);
        // printf("room_index: %d, j: %d, char: %c\n", room, j, g_sm_matrix[room][j]);
        if (g_sm_matrix[room][j] == c)
        {
            // printf("find - !\n");
            return j;
        }
    }
    // printf("return -1\n");
    return -1;
}

//проверка на связь с финишной точкой и на ее доступность
int finish_check(int room)
{
    for(unsigned int i = 0; i < g_vars.list_room[room]->number_of_conn; i++)
    {
        if (g_vars.list_room[room]->conn_pointers[i]->index == (int)g_vars.number_of_rooms - 1)        
        {
            if (find_ch(room, 0, '+') != -1)
            {
                // printf("room: %d finish not actual \n", room);
                return 0;
            }
            else
            {
                // printf("room: %d finish actual \n", room);
                return 1;
            }
        }
    }
    return 0;
}

int search_last_room(int num)
{    
    for (unsigned int i = 0; i < g_vars.number_of_rooms; i++)
    {        
        if (g_cur_rooms[i] == num)
            return i;
    }
    return -1;
}
//  откат до предыдущего состояние
//  1. отмена проставления знаков в матрице смежности
//  2. удаление комнаты из steps
void rollback()
{
    // printf("Matrix before del:\n");
    // print_matrix(g_sm_matrix);
    // print_lst(&g_steps);


    // t_step *del_step = ft_lstlast_pn(g_steps);


    // printf("del_step: %s, list: ", g_vars.list_room[del_step->room]->name);

    // if (del_step->old_ch == ' ')
    int prew = search_last_room(count-1);
    int room = search_last_room(count);
    if (g_sm_matrix[prew][room] == '+')
        full_matrix(prew, room, ' ', ' ');

    // else if (del_step->old_ch == '-')
    else if (g_sm_matrix[prew][room] == ' ')
        full_matrix(prew, room, '-', '+');
    // printf("dell back\n");

    // ft_lst_del_back_pn(&g_steps);

    g_cur_rooms[room] = -1;
    count--;
    // printf("Matrix after del:\n");
    // print_matrix(g_sm_matrix);
    // print_lst(&g_steps);
}

//возврат -2 - если проверка связи неудачная
int room_check(int room, int ch)
{
    if (check_connection(ch))           // проверяем, можем ли мы использовать эту связь
    {
        // ft_lst_add_back_pn(&g_steps, ft_lstnew_pn(ch, g_sm_matrix[room][ch], room)); //добавляем шаг в цепочку
        g_cur_rooms[ch] = ++count;
        if (g_sm_matrix[room][ch] == '-')
        {
            // printf("g_sm_matrix[room][ch] == '-'\n");
            full_matrix(room, ch, ' ', ' ');
        }
        else if (g_sm_matrix[room][ch] == ' ')
        {
            // printf("g_sm_matrix[room][ch] == ' '\n");
            full_matrix(room, ch, '+', '-');
        }
        // print_matrix(g_sm_matrix);
        return(full_current_step(ch));     //может возвращать
    }
    return -3;
}

int find_minus(int room)
{
    // printf("start find_minus\n");
    int ch = 0;
    int a;
    
    while (ch != -1)
    {
        
        ch = find_ch(room, ch, '-');    // находим первый минус, запоминаем место его нахождения - ch, 
                                        // если нам не подходит эта комната, продолжаем просмативать минусы, 
                                        // начиная со следующего ch
        if (ch == -1)
        {
            // printf("continue\n");
            continue;
        }
        
        // printf("- found = %s\n", g_vars.list_room[ch]->name);
        a = room_check(room, ch);
        if (a == -1)
            return -1;
        else if (a == -2)
        {
            // printf("need rollback\n");
            rollback();
            
        }
        ch = find_ch(room, ch + 1, '-');
        // printf("ch = %d\n", ch);
    }
    // printf("find_minus return -2\n");
    // printf("need rollback\n");
    rollback();
    return -2; // не найдена следующая комната
}





//заполнить текущий шаг - рекурсия
//при возможном заполнении двигаемся дальше, если зашли в тупик - откат предыдущих шагов пока не будет возможно сделать следующий шаг
//при возвращении в 0 - откат
//при отсутствии связей - откат
//если есть "+" у назначении проверяются только доступные "-" - далее необходимо будет заменить данные в ячейках - скомпенсировать пути
//необходимо сравнивать место назначения с уже посещенной комнатой
//
int full_current_step(int room)
{
    int a; 

    //проверка на связь с финишом и что эта связь свободна для использования - конец рекурсии

    //!!!! нужно будет почистить по завершении все списки - функции написаны ft_lstclear_....
    if (finish_check(room) || room == (int)g_vars.number_of_rooms - 1)
    {
        // printf("finish_check: OK!\n");
        if (room != (int)g_vars.number_of_rooms - 1)
        {   
            // ft_lst_add_back_pn(&g_steps, ft_lstnew_pn(g_vars.number_of_rooms - 1, ' ', room)); //добавляем последний шаг до финиша в цепочку
            g_cur_rooms[g_vars.number_of_rooms - 1] = ++count;
            full_matrix(room, g_vars.number_of_rooms - 1, '+', ' '); //в матрице отображаем наш ход
        }
        g_vars.number_of_ways++; //увеличиваю поличество путей
        // print_matrix(g_sm_matrix);
        return -1; //код завершения
    }
        
    //проверка на занятость пути - если + ищется свободный -
    if (room != 0 && find_ch(room, 0,'+') != -1)
    {
        // printf("find + : OK!\n");
        return find_minus(room);
    }
    else
    {    
        for (unsigned int i = 0; i < g_vars.list_room[room]->number_of_conn; i++)
        {
            // printf("find connections : OK! %s\n", g_vars.list_room[room]->conn_pointers[i]->name);
            // printf("current room index: %d, check room index: %d, i: %d\n", room, g_vars.list_room[room]->conn_pointers[i]->index, i);
            a = room_check(room, g_vars.list_room[room]->conn_pointers[i]->index);
            // printf("!!!!!!!!!!!\n");
            if (a == -2)
                continue;
            if (a == -1)
                return -1;
        }
    }
    // printf("full_current_step return -2\n");
    rollback();
    return -2;
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
            room = find_ch(room, 0, '+');
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
    
    printf("start alg\n");
    int a;
    g_vars.number_of_ways = 0;
    
    for(unsigned int i = 0; i < g_vars.number_of_rooms; i++)
    {
        g_vars.list_room[i]->index = i;
    }
    
    // print_rooms(1);//0 - печать комнаты, +печать связи - 1

    create_matrix(g_vars.number_of_rooms); // ее потом нужно будет очистить по завершени/ю алгоритма
    g_cur_rooms_create(g_vars.number_of_rooms, 1);


    for (unsigned int i = 0; i < g_vars.list_room[0]->number_of_conn; i++)
    {
       count = -1;
        // ft_lst_add_back_pn(&g_steps, ft_lstnew_pn(0,' ', 0));
        g_cur_rooms[0] = ++count;
        // print_matrix(g_sm_matrix);

        // ft_lst_add_back_pn(&g_steps, ft_lstnew_pn(g_vars.list_room[0]->conn_pointers[i]->index,' ', 0));
        g_cur_rooms[i] = ++count;
        full_matrix(0, g_vars.list_room[0]->conn_pointers[i]->index, '+', ' ');
        // print_matrix(g_sm_matrix);
        //  printf("i: %d\n", i);
        a = full_current_step(g_vars.list_room[0]->conn_pointers[i]->index);
        
        if (a == -2)
            rollback();
        // if (a == -1)
            // ft_lst_add_back_one(&g_fin_ways, ft_lstnew_one(&g_steps));

        // ft_lstclear_pn(&g_steps);
        g_cur_rooms_create(g_vars.number_of_rooms, 0);
    }
    // printf("FINISH MATRIX:\n");
    // print_matrix(g_sm_matrix);
    finish_ways();
    clean_matrix();
}