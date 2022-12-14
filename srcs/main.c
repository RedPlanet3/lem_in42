/**
 * 		General instructions:
 * +1	The executable file must be named lem-in.
 * +2	You must submit a Makefile. That Makefile needs to compile the project and
 * 	must contain the usual rules. It can only recompile the program if necessary.
 * 3	If you are clever, you will use your library for your lem-in. Also submit your folder
 * 	libft including its own Makefile at the root of your repository. Your Makefile
 * 	will have to compile the library, and then compile your project.
 * +4	Your project must be written in C.
 * +5	You have to handle errors in a sensitive manner. In no way can your program quit
 * 	in an unexpected manner (Segmentation fault, bus error, double free, etc)
 * 6	Your program cannot have memory leaks.
 * 7	Within your mandatory part you are allowed to use the following functions
 * 		malloc
 * 		free
 * 		read
 * 		write
 * 		strerror
 * 		perror
 * 		exit
 * +8	You are allowed to use other functions to carry out the bonus part as long as their
 * 	use is justified during your defence.
 * 
 * 		Mandatory part
 * 1	The goal of this project is to find the quickest way to get n ants across the farm.
 * 2	Quickest way means the solution with the least number of lines, respecting the
 * 	output format requested below.
 * 3	Obviously, there are some basic constraints. To be the first to arrive, ants will need
 * 	to take the shortest path (and that isn’t necessarily the simplest). They will also
 * 	need to avoid traffic jams as well as walking all over their fellow ants.
 * 4	At the beginning of the game, all the ants are in the room ##start. The goal is
 * 	to bring them to the room ##end with as few turns as possible. Each room can
 * 	only contain one ant at a time. (except at ##start and ##end which can contain
 * 	as many ants as necessary.)
 * 5	We consider that all the ants are in the room ##start at the beginning of the game.
 * 6	At each turn you will only display the ants that moved.
 * 7	At each turn you can move each ant only once and through a tube (the room at
 * 	the receiving end must be empty).
 * 8	You must to display your results on the standard output in the following format:
 * 		number_of_ants
 * 		the_rooms
 * 		the_links
 * 		
 * 		Lx-y Lz-w Lr-o ...
 * 	x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y,
 * 	w, o represents the rooms’ names.
 */

/**
 * Work process
 * 1. Add error handler for ft_atoi (if get not number)
 * 
 * RULES
 * А)
 * 1. Найти все непересекающиеся пути
 * 2. Пустить по ним поровну
 * Б)
 * 1. Найти все непересекающиеся пути
 * 2. Добавить зависимость от веса пути (3 пути 3/3/9 и 15 муравьев)
 * В)
 * 1. Найти оптимальные пути (не самые короткие)
 * 2. Выбор оптимального сочетания путей в зависимости от количества муравьев и весов путей
 * 
 * Поиск путей:
 * 1) Найти все пути и выбрать из них короткий, непересекажищийся и т.д.
 * 2) Найти первый попавшийся и остальные только если они не пересекаются с ним.
 */

#include "../includes/lem_in.h"

t_vars			g_vars = {
	.ant_number = 0,
	.ant_number_flag = 1,
	.end_flag = 0,
	.end_rooms_flag = 0,
	.err_msg = NULL,
	.start_flag = 0,
	.list_room = NULL,
	.start_room = NULL,
	.end_room = NULL,
	.number_of_rooms = 0
};

static int		ft_exit(void) {
	print_debug("ft_exit start\n");
	unsigned int	i = 0;

	if (g_vars.err_msg) {
		write(1, g_vars.err_msg, ft_strlen(g_vars.err_msg));
		write(1, "\n", 1);
		free(g_vars.err_msg);
	}

	print_debug("ft_exit start clean list rooms. room numbers = %d\n", g_vars.number_of_rooms);
	while(i < g_vars.number_of_rooms){
		free(g_vars.list_room[i]->name);
		free(g_vars.list_room[i]);
		i++;
	}
	print_debug("ft_exit start clean list rooms. i = %d\n", i);
	if (g_vars.list_room){
		print_debug("ft_exit start clean this list\n");
		free(g_vars.list_room);
	}

	if(g_vars.start_room){
		free(g_vars.start_room->name);
		free(g_vars.start_room);
	}

	if(g_vars.end_room){
		free(g_vars.end_room->name);
		free(g_vars.end_room);
	}
	
	print_debug("ft_exit finish success\n");
	return g_vars.end_flag;
}

int				main(void) {
	int			ret;
	char		*buf;

	print_debug("Main start\n");

	while((ret = get_next_line(0, &buf)) > 0) {
		print_debug("Main gnl next iteration: %s\n", buf);
		if (ft_parser(buf))
			goto exit;								// Free memory for error in ft_parser
		free(buf);
	}
	free(buf);

	print_debug("Main finish success\n");
	return ft_exit();
exit:
	free(buf);
	print_debug("Main finish with error\n");
	return ft_exit();
}