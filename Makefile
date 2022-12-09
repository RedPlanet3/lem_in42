NAME		= lem-in

SRCS		= $(shell find ./srcs -type f -name "*.c")

OBJS		= $(SRCS:.c=.o)

FLAGS		= -Wall -Wextra -Werror -g

CC			= gcc

LD			= ld

RM			= rm -rf

.PHONY:		all clean fclean re

.c.o:
			$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			(cd libft; make; cp libft.a ../includes/.)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS) ./includes/libft.a

all:		$(NAME)

clean:
			(cd libft; make clean)
			$(RM) $(OBJS)

fclean:
			(cd libft; make fclean)
			(cd includes; rm libft.a)
			$(RM) $(OBJS) $(NAME)

re:			fclean all