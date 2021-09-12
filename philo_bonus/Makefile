PROGNAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = $(addprefix philo_bonus_, $(addsuffix .c, main msg_box preproc threads time atoi actions))
HEADERS = philo_headers.h philo_structs.h
%.o: %.c ${HEADERS}
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
MINOBJS = ${SRC:.c=.o}
all:  ${PROGNAME}
${PROGNAME}: ${MINOBJS}
		${CC} ${CFLAGS} ${MINOBJS} -o ${PROGNAME}
run:
		./${PROGNAME}
clean:
		rm -f ${MINOBJS}
fclean: clean
		rm -f $(NAME) ${PROGNAME}
re: fclean all