#include "../includes/lem_in.h"

static enum str_type	ft_get_type(char *str){
	enum str_type	return_type;
	
	print_debug("ft_get_type start\n");

	if (g_vars.ant_number_flag) {						// Get ant number
		return return_type = ANTS_NUMBER;
	} else if (!ft_strcmp(str, "##start") ||			// Get start str
		g_vars.start_flag == 1) {
		return return_type = ROOM_START;
	} else if (!ft_strcmp(str, "##end") ||				// Get end str
				g_vars.end_flag == 1) {
		return return_type = ROOM_END;
	} else if (g_vars.end_rooms_flag == 0) {			// Get rooms
		return return_type = ROOM_ADD;
	} else if (g_vars.end_rooms_flag) {					// Get connections
		return return_type = ROOM_CONN;
	}

	g_vars.err_msg = ft_strjoin(ft_strdup("Bad map: "), str);
	free(str);

	print_debug("ft_get_type finish with ERROR\n");
	return return_type = STR_ERROR;						// Bad str
}

static t_room			*ft_create_room(char **args) {
	print_debug("ft_create_room start.\n");
	t_room	*room;

	if(!(room = (t_room *)malloc(sizeof(t_room)))){
		g_vars.err_msg = ft_strdup("malloc error");
		goto error;
	}

	room->name = args[0];
	room->x = ft_atoi(args[1]);							// Errors not handle
	room->y = ft_atoi(args[2]);							// Errors not handle
	free(args[1]);
	free(args[2]);

	print_debug("ft_create_room finish success\n");
	return room;

error:
	free(args[0]);
	free(args[1]);
	free(args[2]);

	print_debug("ft_create_room finish with ERROR\n");
	return NULL;
}

static int				ft_get_str_number(char **list){
	// Counts the number of rows in the list "str"
	int	ret = 0;

	if(!list)
		return 0;

	while(*list){
		ret++;
		list++;
	}
	
	return ret;
}

static int				ft_get_start_room(char *str){
	print_debug("ft_get_start_room start. str: %s; start_flag = %d\n",
				str, g_vars.start_flag);
	char	**list;

	if (g_vars.start_flag == 2)
		goto error;

	if (!g_vars.start_flag) {
		g_vars.start_flag = 1;
		return SUCCESS;
	}

	list = ft_split(str, ' ');
	if(ft_get_str_number(list) != 3)
		goto error;
	if (!(g_vars.start_room = ft_create_room(list)))
		goto error;

	g_vars.start_flag = 2;

	print_debug("ft_get_start_room finish success\n");
	return SUCCESS;

error:
	g_vars.err_msg = ft_strjoin(ft_strdup("Bad map: "), str);
	free(str);

	print_debug("ft_get_start_room finish with ERROR\n");
	return ERROR;										// Bad str
}

static int				ft_get_end_room(char* str){
	print_debug("ft_get_end_room start. str: %s; end_flag = %d\n",
				str, g_vars.end_flag);
	char	**list;

	if (g_vars.end_flag == 2)							// If double end lable in map
		goto error;

	if (!g_vars.end_flag) {								// For scip end lable
		g_vars.end_flag = 1;
		return SUCCESS;
	}

	list = ft_split(str, ' ');
	if(ft_get_str_number(list) != 3)
		goto error;
	if (!(g_vars.end_room = ft_create_room(list)))
		goto error;

	g_vars.end_flag = 2;

	print_debug("ft_get_end_room finish success\n");
	return SUCCESS;

error:
	g_vars.err_msg = ft_strjoin(ft_strdup("Bad map: "), str);
	free(str);

	print_debug("ft_get_end_room finish with ERROR\n");
	return ERROR;										// Bad str
}

static int				ft_get_ant_number(char *str){
	print_debug("ft_get_ant_number start. str: %s\n", str);
	g_vars.ant_number_flag = 0;

	g_vars.ant_number = ft_atoi(str);					// Errors not handle

	print_debug("ft_get_ant_number finish success\n");
	return SUCCESS;
}

static int				ft_put_room_to_list(t_room *next_room){
	print_debug("ft_put_room_to_list start\n");
	t_room			**temp;
	unsigned int	i;
	
	// size = ft_number_of_rooms(g_vars.list_room);
	// print_debug("ft_put_room_to_list size = %d\n", size);
	if (g_vars.list_room == NULL) {
		g_vars.list_room = (t_room **)malloc(sizeof(t_room *) * 2);
		if (!g_vars.list_room)
			goto error;
		g_vars.list_room[0] = next_room;
		print_debug("ft_put_room_to_list finish success\n");
		return SUCCESS;
	} else {
		temp = (t_room **)malloc(sizeof(t_room *)
				* (g_vars.number_of_rooms + 1));
		if (!temp)
			goto error;
	}

	for(i = 0; i < g_vars.number_of_rooms; i++)
		temp[i] = g_vars.list_room[i];
	temp[i] = next_room;
	g_vars.number_of_rooms += 1;
	free(g_vars.list_room);
	g_vars.list_room = temp;

	print_debug("ft_put_room_to_list finish success\n");
	return SUCCESS;
error:
	print_debug("ft_put_room_to_list finish with ERROR\n");
	g_vars.err_msg = ft_strdup("malloc error");
	return ERROR;
}

static int				ft_add_room(char *str){
	print_debug("ft_add_room start. str: %s\n",
				str);
	char	**list;
	t_room	*temp;

	list = ft_split(str, ' ');
	if (ft_get_str_number(list) != 3) {					// Str with rooms end
		g_vars.end_rooms_flag = 1;
		goto success;
	}

	if (!(temp = ft_create_room(list)) ||
		ft_put_room_to_list(temp))
		goto error;

success:
	print_debug("ft_add_room finish success\n");
	return SUCCESS;

error:
	g_vars.err_msg = ft_strjoin(ft_strdup("Bad map: "), str);
	free(str);

	print_debug("ft_add_room finish with ERROR\n");
	return ERROR;										// Bad str
}

static int				ft_add_connection(char *str){
	print_debug("ft_add_connection start. str: %s\n",
			str);

	write(1, str, ft_strlen(str));
	write(1, "\n", 1);

	print_debug("ft_add_connection finish success\n");
	return SUCCESS;

// error:
// 	g_vars.err_msg = ft_strjoin(ft_strdup("Bad map: "), str);
// 	free(str);

// 	print_debug("ft_add_connection finish with ERROR\n");
// 	return ERROR;										// Bad str
}

int						ft_parser(char *str){
	// Parser for strings in map
	enum str_type	type;
	int				ret;
	char			*temp;

	print_debug("ft_parser start\n");

	temp = ft_strtrim(str, " \t\n");
	type = ft_get_type(temp);							// Get type
	free(temp);
	switch (type) {
	case ANTS_NUMBER:
		ret = ft_get_ant_number(str);					// Get ant number
		break;
	case ROOM_START:
		ret = ft_get_start_room(str);					// Create start room
		break;
	case ROOM_END:
		ret = ft_get_end_room(str);						// Create end room
		break;
	case ROOM_ADD:
		ret = ft_add_room(str);							// Create end room
		break;
	case ROOM_CONN:
		ret = ft_add_connection(str);		// Create end room
		break;
	default:
		ret = 1;							// Return error
	};

	if (ret)
		return ERROR;

	print_debug("ft_parser finish success\n");
	return SUCCESS;
}