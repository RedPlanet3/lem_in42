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
	NEXT_STR	= 3,
	STR_ERROR	= -1
};

typedef struct 			s_vars {
	unsigned int		ant_number;
	unsigned short int	ant_number_flag;
	unsigned short int	start_flag;
	unsigned short int	end_flag;
	char				*err_msg;
}						t_vars;

extern t_vars	g_vars;

int				ft_parser(char *str);
int				main(void);

#endif