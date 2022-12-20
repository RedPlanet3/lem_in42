#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

// # define DEBUG
# define SUCCESS		0
# define ERROR			1
# define BUFF_SIZE		1024

#ifdef DEBUG
# include <stdio.h>
# define print_debug(a, args...) printf("name_in_box: " a, ## args)
#else
# define print_debug(a, args...)
#endif

enum str_type {
	ANTS_NUMBER	= 0,
	ROOM_START	= 1,
	ROOM_END	= 2,
	ROOM_ADD	= 3,
	ROOM_CONN	= 4,
	COMMENT		= 5,
	STR_ERROR	= -1
};

typedef struct 			s_room {
	char				*name;				// Room name
	unsigned int		x;					// X coordinate
	unsigned int		y;					// Y coordinate
	char				**connections;		// Names of rooms for connections
	struct s_room		**conn_pointers;	// Connect-pointer with connect-room
	unsigned int		number_of_conn;		// Number of connections
	int					index;
}						t_room;

typedef struct 			s_way {
	unsigned int		count_of_rooms;		// Count of rooms
	t_room				**rooms;			// Way rooms
}						t_way;


typedef struct 			s_vars {
	unsigned int		ant_number;			// Number of ants
	unsigned short int	ant_number_flag;	// For read ants number
	unsigned short int	start_flag;			// Found the start room
	unsigned short int	end_flag;			// Found the end room
	char				*err_msg;			// For error message
	int					ret_value;			// Return value for the whole program
	unsigned short int	end_rooms_flag;		// Rooms reading finish
	t_room				*start_room;		// Start room pointer
	t_room				*end_room;			// End room pointer
	t_room				**list_room;		// List rooms pointer
	unsigned int		number_of_rooms;	// Number of rooms
	t_way				**list_ways;		// List ways piinter
	unsigned int		number_of_ways;		// Number of ways
}						t_vars;

extern t_vars	g_vars;

int				ft_delete_empty_rooms(void);
int				ft_create_ways_table(void);
int				ft_parser(char *str);
int				main(void);

char **sm_matrix;

unsigned int		number_of_ways;

typedef struct 			s_fin_ways {
	t_step				**step_pointers;	// Connect-pointer with connect-room
	struct	s_fin_ways 	next;
}						t_fin_ways;

extern t_fin_ways **g_fin_ways;


#endif