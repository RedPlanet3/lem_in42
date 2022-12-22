#include "../includes/lem_in.h"
// t_step **steps;
// char **sm_matrix;


// Проверка на использованные кормнаты в пути и на возврат в старт
// 0 - связь использовать нельзя
int check_connection(int dest) 
{
    t_step *tmp_steps = *steps;

    while (tmp_steps->next != NULL)
	{
		if(tmp_steps->room == dest)
            return 0;
        else if(tmp_steps->room == 0)
            return 0;
		tmp_steps = tmp_steps->next;
	}
    return 1;
}

void create_matrix(unsigned int number_of_rooms)
{
    sm_matrix = (char**)malloc(number_of_rooms * sizeof(char*));
    for (unsigned int i = 0; i<number_of_rooms; i++)
    {
        sm_matrix[i] = (char*)malloc(number_of_rooms * sizeof(char));
        for (unsigned int j = 0; j<number_of_rooms; j++)
        {
            sm_matrix[i][j] = ' ';
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
        if (sm_matrix[room][j] == c)
            return j;
    }
    return -1;
}

//проверка на связь с финишной точкой и на ее доступность
int finish_check(int room)
{
    for(unsigned int i = 0; i < g_vars.list_room[room]->number_of_conn; i++)
    {
        if (int(g_vars.list_room[room]->conn_pointers[i]->index) == g_vars.number_of_rooms - 1)        
        {
            if (find_ch(room, 0, '+'))
                return 0;
            else
                return 1;
        }
    }
    return 0;
}

//  откат до предыдущего состояние
//  1. отмена проставления знаков в матрице смежности
//  2. удаление комнаты из steps
void rollback()
{
    t_step *del_step = ft_lstlast_pn(*steps);
    if (del_step->old_ch == ' ')
        full_matrix(del_step->prev_room, del_step->room, ' ', ' ');
    else if (del_step->old_ch == '-')
        full_matrix(del_step->prev_room, del_step->room, '-', '+');
    ft_lst_del_back_pn(steps);
}

//возврат -2 - если проверка связи неудачная
int room_check(int room, int ch)
{
    if (check_connection(ch))           // проверяем, можем ли мы использовать эту связь
    {
        ft_lst_add_back_pn(steps, ft_lstnew_pn(ch, '-', room)); //добавляем шаг в цепочку
        full_matrix(room, ch, ' ', ' ');
        return(full_current_step(ch));     //может возвращать
    }
    return -2;
}

int find_minus(int ch, int room)
{
    ch = 0;
    int a;
    while (ch != -1)
    {
        ch = find_ch(room, ch, '-');    // находим первый минус, запоминаем место его нахождения - ch, 
                                        // если нам не подходит эта комната, продолжаем просмативать минусы, 
                                        // начиная со следующего ch
        a = room_check(room, ch);
        if (a == -1)
            return -1;
        else if (a == -2)
            rollback();
        ch = find_ch(room, ch + 1, '-'); 
    }
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
    int ch;
    int a;
    // if (room == -1)
    //     return -1;
    // if (room == -2)
        //шагать дальше

    //проверка на связь с финишом и что эта связь свободна для использования - конец рекурсии

    //!!!! нужно будет почистить по завершении все списки - функции написаны ft_lstclear_....
    if (finish_check(room))
    {
        ft_lst_add_back_pn(steps, ft_lstnew_pn(g_vars.number_of_rooms - 1, ' ', room)); //добавляем последний шаг до финиша в цепочку
        full_matrix(room, g_vars.number_of_rooms - 1, '+', ' '); //в матрице отображаем наш ход
        g_vars.number_of_ways++; //увеличиваю поличество путей
        return -1; //код завершения
    }
        
    //проверка на занятость пути - если + ищется свободный -
    if (room != 0 && find_ch(room, 0,'+') != -1)
    {
        return find_minus(ch, room);
        // int a = find_minus(ch, room);
        // if (a == -2)
        // {            
        //     rollback(room); // откат
        //     return -2; //если нет доступных комнат откат?
        // }
        // else if (a == -1)
        //     return -1;
        // else
        //     write(1, "check + error" , ft_strlen("check + error"));
    }
    else
    {    
        for (int i = 0; i < g_vars.list_room[room]->number_of_conn; i++)
        {
            a = room_check(room, g_vars.list_room[room]->conn_pointers[i]->index);
            if (a == -2)
                rollback();
            if (a == -1)
                return -1;
            // if (check_connection(g_vars.list_room[room]->conn_pointers[i]->index))
            // {                        
            //     ft_lst_add_back_pn(steps, ft_lstnew_pn(g_vars.list_room[room]->conn_pointers[i]->index, '+', room)); //добавляем шаг в цепочку
            //     full_matrix(room, g_vars.list_room[room]->conn_pointers[i]->index, '+', '-');
            //     if (full_current_step(g_vars.list_room[room]->conn_pointers[i]->index) == -2)//может возвращать
            //     {
            //         rollback(room); // откат
            //     }
            // }
            // else
            //     continue;
        }
    }
    return -2;
}


void full_finish_ways()
{

    
}


void alg()
{
    int a;
    g_vars.number_of_ways = 0;
   
    for(int i; i < g_vars.number_of_rooms; i++)
    {
        g_vars.list_room[i]->index = i;
    }
   
    create_matrix(g_vars.number_of_rooms); // ее потом нужно будет очистить по завершени/ю алгоритма

    for (int i = 0; i < g_vars.list_room[0]->number_of_conn; i++)
    {
        ft_lst_add_back_pn(steps, ft_lstnew_pn(0,' ', 0));
        ft_lst_add_back_pn(steps, ft_lstnew_pn(g_vars.list_room[0]->conn_pointers[i]->index,' ', 0));
        full_matrix(0, g_vars.list_room[0]->conn_pointers[i]->index, '+', ' ');
        a = full_current_step(g_vars.list_room[0]->conn_pointers[i]->index);
        if (a == -2)
            rollback();
        if (a == -1)
            ft_lst_add_back_one(g_fin_ways, ft_lstnew_one(steps));
        ft_lstclear_pn(steps);
    }

    
 
    

}