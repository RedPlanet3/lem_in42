#include "../includes/lem_in.h"
t_step **steps;

// Проверка на использованные кормнаты в пути и на возврат в старт
// 0 - связь использовать нельзя

int check_connection(int dest) 
{
    t_step *tmp_steps = steps;

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


int finish_check(int room)
{
    for(int i = 0; i < g_vars.list_room[room]->number_of_conn; i++)
    {
        if (g_vars.list_room[room]->conn_pointers[i]->index == g_vars.number_of_rooms - 1)        
        {
            if (find_ch(room, 0, '+'))
                return 0;
            else
                return 1;
        }
    }
    return 0;
}

int find_plus(int ch, int room)
{
    ch = 0;
    while (ch != -1)
    {
        ch = find_ch(room, ch, '-');    // находим первый минус, запоминаем место его нахождения - ch, 
                                        // если нам не подходит эта комната, продолжаем просмативать минусы, 
                                        // начиная со следующего ch
        if (check_connection(ch))     // проверяем, можем ли мы использовать эту связь
        {
            ft_lst_add_back_pn(steps, ft_lstnew_pn(ch, '-')); //добавляем шаг в цепочку
            full_matrix(room, ch, ' ', ' ');
            return full_current_step(ch);//может возвращать
        }
        ch = find_ch(room, ch + 1, '-'); 
    }
    return -2; // не найдена следующая комната
}

void rollback(int room)
{
    t_step *del_step = ft_lstlast_pn(steps);
    if(del_step->old_ch == ' ')
        full_matrix(room, del_step->room, ' ', ' ');
    if(del_step->old_ch == '-')
        full_matrix(room, del_step->room, '-', '+');
    ft_lst_del_back_pn(steps);
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
    if (room == -1)
        return -1;
    // if (room == -2)
        //шагать дальше

    //проверка на связь с финишом и что эта связь свободна для использования - конец рекурсии

    //!!!! нужно будет почистить по завершении все списки - функции написаны ft_lstclear_....
    if (finish_check(room))
    {
        ft_lst_add_back_pn(steps, ft_lstnew_pn(g_vars.number_of_rooms - 1, ' ')); //добавляем последний шаг до финиша в цепочку
        full_matrix(room, g_vars.number_of_rooms - 1, '+', '-'); //в матрице отображаем наш ход
        ft_lst_add_back_one(g_fin_ways, ft_lstnew_one(steps)); //добавляем готовую цепочку в список цепочек
        number_of_ways++; //увеличиваю поличество путей
        return -1; //код завершения
    }
        
    //проверка на занятость пути - если + ищется свободный -
    if (room != 0 && find_ch(room, 0,'+') != -1)
    {
        int a = find_plus(ch, room);
        if (a == -2)
        {            
            rollback(room); // откат
            return ; //если нет доступных комнат откат?
        }
        else
            full_current_step(a); //иначе запускаем функцию для следующего шага
            return a; //что вернуть?
    }

    for (int i = 0; i < g_vars.list_room[room]->number_of_conn; i++)
    {
        if (check_connection(g_vars.list_room[room]->conn_pointers[i]->index))
        {                        
            ft_lst_add_back_pn(steps, ft_lstnew_pn(g_vars.list_room[room]->conn_pointers[i]->index, '+')); //добавляем шаг в цепочку
            full_matrix(room, g_vars.list_room[room]->conn_pointers[i]->index, '+', '-');
            if (full_current_step(g_vars.list_room[room]->conn_pointers[i]->index) == -2)//может возвращать
            {
                rollback(room); // откат
            }
        }
        else
            continue;
    }
    return -2;
}





void alg()
{
    number_of_ways = 0;
    // char* ways;
    for(int i; i < g_vars.number_of_rooms; i++)
    {
        g_vars.list_room[i]->index = i;
    }
    // ways[i] = (char*)malloc(g_vars.number_of_rooms * sizeof(char));
    create_matrix(g_vars.number_of_rooms);

    for (int i = 0; i < g_vars.list_room[0]->number_of_conn; i++)
    {
        ft_lst_add_back_pn(steps, ft_lstnew_pn(0,' '));
        full_current_step(0);


        ft_lst_del_back_pn(steps); // del steps
        ft_lstclear_pn(steps);
    }
    ft_lst_del_back_pn(steps); // del steps
    
    // while (/* condition */)
    // {
        
    // }
    

}