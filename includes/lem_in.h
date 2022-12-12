#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

# define DEBUG
# define SUCCESS		0
# define ERROR		1
# define BUFF_SIZE	1024

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
	STR_ERROR	= -1
};

typedef struct 			s_room {
	char				*name;				// Room name
	unsigned int		x;					// X coordinate
	unsigned int		y;					// Y coordinate
}						t_room;

typedef struct 			s_vars {
	unsigned int		ant_number;			// Number of ants
	unsigned short int	ant_number_flag;	// For read ants number
	unsigned short int	start_flag;			// Found the start room
	unsigned short int	end_flag;			// Return value for the whole program
	char				*err_msg;			// For error message
	unsigned short int	end_rooms_flag;		// Rooms reading finish
	t_room				*start_room;		// Start room pointer
	t_room				*end_room;			// End room pointer
	t_room				**list_room;		// List rooms pointer
	unsigned int		number_of_rooms;	// Number of rooms
}						t_vars;


extern t_vars	g_vars;

int				ft_parser(char *str);
int				main(void);

#endif