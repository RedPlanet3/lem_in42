#include "../includes/lem_in.h"

static enum str_type	ft_get_type(char *str){
	enum str_type	return_type;
	
	print_debug("ft_get_type start\n");

	if (!ft_strcmp(str, "##start") ||
		g_vars.start_flag == 1) {
		return return_type = ROOM_START;
	} else if (!ft_strcmp(str, "##end") ||
				g_vars.end_flag == 1) {
		return return_type = ROOM_END;
	} else if (g_vars.ant_number_flag) {
		return return_type = ANTS_NUMBER;
	}

	g_vars.err_msg = ft_strjoin(ft_strdup("Bad map: "), str);
	free(str);

	print_debug("ft_get_type finish with ERROR\n");
	return return_type = STR_ERROR;					// Bad str
}

static int				ft_get_start(char *str){
	print_debug("ft_get_start start. str: %s; start_flag = %d\n",
				str, g_vars.start_flag);
	
	if (g_vars.start_flag == 2)
		goto error;

	if (!g_vars.start_flag) {
		g_vars.start_flag = 1;
		return SUCCESS;
	}

	// Need handler

	g_vars.start_flag = 2;

	print_debug("ft_get_start finish success\n");
	return SUCCESS;

error:
	g_vars.err_msg = ft_strjoin(ft_strdup("Bad map: "), str);
	free(str);

	print_debug("ft_get_start finish with ERROR\n");
	return ERROR;					// Bad str
}

static int				ft_get_end(char* str){
	print_debug("ft_get_end start. str: %s; end_flag = %d\n",
				str, g_vars.end_flag);

	if (g_vars.end_flag == 2)
		goto error;

	if (!g_vars.end_flag) {
		g_vars.end_flag = 1;
		return SUCCESS;
	}

	// Need handler

	g_vars.end_flag = 2;

	print_debug("ft_get_end finish success\n");
	return SUCCESS;

error:
	g_vars.err_msg = ft_strjoin(ft_strdup("Bad map: "), str);
	free(str);

	print_debug("ft_get_end finish with ERROR\n");
	return ERROR;					// Bad str
}

static int				ft_get_ant_number(char *str){
	print_debug("ft_get_end start. str: %s\n", str);
	g_vars.ant_number_flag = 0;

	// Need handler

	print_debug("ft_get_ant_number finish success\n");
	return SUCCESS;
}

int		ft_parser(char *str){
	// Parser for strings in map
	enum str_type	type;

	print_debug("ft_parser start\n");

	type = ft_get_type(ft_strtrim(str, " \t\n"));			// Get type
	switch (type) {
	case ANTS_NUMBER:
		if(ft_get_ant_number(str))		// Get ant number
			return ERROR;
		break;
	case ROOM_START:
		if(ft_get_start(str))			// Create start room
			return ERROR;
		break;
	case ROOM_END:
		if(ft_get_end(str))				// Create end room
			return ERROR;
		break;
	case NEXT_STR:
		break;
	default:
		return ERROR;					// If return error
	};

	print_debug("ft_parser finish success\n");
	return SUCCESS;
}