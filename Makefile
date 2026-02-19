SRC = main.c \
	utils.c \
	utils_philo.c \
	init_and_check.c \
	check_limits.c \

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