#include "../includes/lem_in.h"

static enum str_type	ft_get_type(char *str){
	enum str_type	return_type;
	
	if (!ft_strcmp(str, "##start")) {
		g_vars.start_flag = 1;
		return return_type = ROOM_START;
	} else if (!ft_strcmp(str, "##end")) {
		g_vars.end_flag = 1;
		return return_type = ROOM_END;
	} else if (g_vars.ant_number_flag) {
		g_vars.end_flag = 1;
		return return_type = ANTS_NUMBER;
	}
	g_vars.err_msg = ft_strjoin(ft_strdup("Bad map: "), str);
	free(str);

	return return_type = STR_ERROR;					// Bad str
}

static int				ft_get_start(char *str){
	write(1, "ft_get_start\n", 13);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return SUCCESS;
}

static int				ft_get_end(char* str){
	write(1, "ft_get_end\n", 11);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return SUCCESS;
}

static int				ft_get_ant_number(char *str){
	write(1, "ft_get_ant_number\n", 18);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return SUCCESS;
}

int		ft_parser(char *str){
	enum str_type	type;
	
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
	default:
		return ERROR;					// If return error
	};

	return SUCCESS;
}