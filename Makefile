NAME		= lem-in

SRCS		= $(shell find ./srcs -type f -name "*.c")

OBJS		= $(SRCS:.c=.o)

FLAGS		= -Wall -Wextra -Werror

CC			= gcc

RM			= rm -rf

.PHONY:		all clean fclean re

.c.o:
			$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:
			$(RM) $(OBJS) $(NAME)

re:			fclean all