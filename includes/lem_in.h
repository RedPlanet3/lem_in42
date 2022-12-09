#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

# define SUCCESS		0
# define ERROR		1
# define BUFF_SIZE	1024

enum str_type {
	ANTS_NUMBER	= 0,
	ROOM_START	= 1,
	ROOM_END	= 2,
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