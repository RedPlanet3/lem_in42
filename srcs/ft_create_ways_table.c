#include "../includes/lem_in.h"

static unsigned int		way_length;
static t_room			**tmp_way;

static int		ft_check_to_have_room_in_queue(t_room *room){
	unsigned int i = 0;

	while(i < way_length){
		if(room == tmp_way[i])
			return 1;
	}

	return 0;
}

static int		ft_remove_last_room(void){
	print_debug("ft_remove_last_room start\n");
	t_room			**temp_list = NULL;
	unsigned int	i;

	if(way_length != 0){
		if(!(temp_list = (t_room**)malloc(sizeof(t_room) * (way_length - 1))))
			goto error;
		for(i = 0; i < (way_length - 1); i++)
			temp_list[i] = tmp_way[i];
		free(tmp_way);
		tmp_way = temp_list;
		way_length -= 1;
	}

	print_debug("ft_remove_last_room finish success\n");
	return SUCCESS;
error:
	print_debug("ft_remove_last_room finish with error\n");
	return ERROR;
}

static t_way	*ft_create_way(void){
	print_debug("ft_create_way finish success\n");
	t_way	*new_way;

	if(!(new_way = (t_way*)malloc(sizeof(t_way))))
		goto error;
	new_way->count_of_rooms = way_length;
	new_way->rooms = tmp_way;

	print_debug("ft_create_way finish success\n");
	return new_way;
error:
	g_vars.err_msg = ft_strdup("malloc error");
	g_vars.end_flag = -1;
	
	print_debug("ft_create_way finish with ERROR\n");
	return NULL;
}

static int		ft_add_one_way_in_table(void){
	print_debug("ft_add_one_way_in_table finish success\n");
	t_way	**tmp;

	if(g_vars.number_of_ways == 0){
		if(!(g_vars.list_ways = (t_way**)malloc(sizeof(t_way*))) ||
			!(g_vars.list_ways[0] = ft_create_way()))
			goto error;
	} else {
		if(!(tmp = (t_way**)malloc(sizeof(t_way*)
							* (g_vars.number_of_ways + 1))))
			goto error;
		for(unsigned int i = 0; i < g_vars.number_of_ways; i++)
			tmp[i] = g_vars.list_ways[i];
		tmp[g_vars.number_of_ways] = ft_create_way();
		free(g_vars.list_ways);
		g_vars.list_ways = tmp;
	}
	g_vars.number_of_ways += 1;


	print_debug("ft_add_one_way_in_table finish success\n");
	return SUCCESS;
error:
	g_vars.err_msg = ft_strdup("malloc error");
	g_vars.end_flag = -1;
	
	print_debug("ft_add_one_way_in_table finish with ERROR\n");
	return ERROR;
}

static int		ft_add_one_room(t_room *next_room){
	print_debug("ft_add_one_room start. way_length = %d\n",
				way_length);
	t_room	**tmp;

	if(way_length == 0){
		if(!(tmp_way = (t_room**)malloc(sizeof(t_room*))))
			goto error;
		tmp_way[0] = g_vars.start_room;
	} else {
		if(!(tmp = (t_room**)malloc(sizeof(t_room*) * (way_length + 1))))
			goto error;
		for(unsigned int i = 0; i < way_length; i++)
			tmp[i] = tmp_way[i];
		tmp[way_length] = next_room;
		free(tmp_way);
		tmp_way = tmp;
		way_length += 1;
	}

	print_debug("ft_add_one_room finish success\n");
	return SUCCESS;
error:
	g_vars.err_msg = ft_strdup("malloc error");
	g_vars.end_flag = -1;
	
	print_debug("ft_add_one_room finish with ERROR\n");
	return ERROR;
}

static int		ft_fix_way(void){
	print_debug("ft_fix_way finish success\n");

	if(ft_add_one_room(g_vars.end_room) ||
		ft_add_one_way_in_table())
		goto error;
	way_length = 0;
	if(ft_add_one_room(NULL))								// Add start room in queue only
		goto error;

	print_debug("ft_fix_way finish success\n");
	return SUCCESS;
error:
	g_vars.err_msg = ft_strdup("malloc error");
	g_vars.end_flag = -1;
	
	print_debug("ft_fix_way finish with ERROR\n");
	return ERROR;
}

static int		ft_next_iteration(t_room **tmp_way){
	print_debug("ft_next_iteration start. way_length = %d; number_of_ways = %d\n",
				way_length, g_vars.number_of_ways);

	free(tmp_way);

	print_debug("ft_next_iteration finish success\n");
	return SUCCESS;
// error:
// 	print_debug("ft_next_iteration finish with ERROR\n");
// 	return ERROR;
}

static int		ft_handle_next_connections(t_room *room){
	print_debug("ft_handle_next_connections start. room_name = %s\n",
				room->name);
	unsigned int i = 0;

	while(i < room->number_of_conn){
		write(1, "next iterate. name connection = ", 33);
		write(1, room->connections[i], ft_strlen(room->connections[i]));
		write(1, "\n", 1);
		// iterate all combinations ways
		if(room->conn_pointers[i] == g_vars.end_room){
			if(ft_fix_way())
				goto error;
			i++;
			continue;
		} else if (room->conn_pointers[i] == g_vars.start_room ||
					ft_check_to_have_room_in_queue(room->conn_pointers[i])){
			i++;
			continue;
		} else {
			if(ft_add_one_room(room->conn_pointers[i]))
				goto error;
			ft_handle_next_connections(room->conn_pointers[i]);
		}
	}
	if(ft_remove_last_room())
		goto error;

	print_debug("ft_handle_next_connections finish success\n");
	return SUCCESS;
error:
	print_debug("ft_handle_next_connections finish with error\n");
	return ERROR;
}

int				ft_create_ways_table(void){
	print_debug("ft_create_ways_table start\n");
	//iterate all rooms and get allways
	// Create first tmp_way for start iteration
	unsigned int	i = 0;

	if(g_vars.start_room->number_of_conn == 0 ||	// No connection in start room
		ft_add_one_room(NULL))						// Add start room in way
		goto error;

	while(i < g_vars.start_room->number_of_conn){
		ft_handle_next_connections(g_vars.start_room->conn_pointers[i]);
	}

	if(ft_next_iteration(tmp_way))
		goto error;

	print_debug("ft_create_ways_table finish success\n");
	return SUCCESS;

error:
	if(g_vars.end_flag == 0){
		g_vars.err_msg = ft_strdup("Bad map: connections error");
		g_vars.end_flag = -1;
	}
	free(tmp_way);

	print_debug("ft_create_ways_table finish with ERROR\n");
	return ERROR;
}