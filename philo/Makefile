SRC = main.c \
	utils.c \
	init_and_check.c \
	check_limits.c \
	activity.c \
	death.c \

OBJ = $(SRC:.c=.o)

CC = cc -Wall -Werror -Wextra -g3
NAME = philo


all: ${NAME}

${NAME}: ${OBJ}
		${CC} ${OBJ} -o ${NAME}

clean:
		rm -f ${OBJ}

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean re fclean