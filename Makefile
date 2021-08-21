SRCS		=	./ft_atoi.c \
			./ft_strlen.c \
			./ft_itoa.c \
			./server.c \
			./client.c

SRCS_lib	=	./ft_atoi.c \
			./ft_strlen.c \
			./ft_itoa.c \

HEADER		=	minitalk.h

OBJS		=	${SRCS:.c=.o}
OBJS_lib	=	${SRCS_lib:.c=.o}

NAME		=	 minitalk

CFLAGS		=	-Wall -Wextra -Werror

.c.o:
			cc ${CFLAGS} -c $< -o ${<:.c=.o}

all:		server client

server:		${HEADER} ${SRCS_lib} ./server.c
		gcc ${CFLAGS} -o server ${SRCS_lib} ./server.c

client:		${HEADER} ${SRCS_lib} ./client.c
		gcc ${CFLAGS} -o client ${SRCS_lib} ./client.c

${NAME}:	all


.PHONY:		clean fclean all re

bonus: 		all

clean:
		rm -f ${OBJS}


fclean:		clean
		rm -f client server

re:		fclean all
