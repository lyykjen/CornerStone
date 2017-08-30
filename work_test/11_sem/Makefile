CC=gcc

CFLAGS 	  = -O3 -Wall -std=gnu11 -I./ -I/usr/include/ -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib

SRC1 = sem1.c
SRC2 = sem2.c
SRC3 = sem3.c

LIB ?= -lm -lpthread

BIN1 = sem1
BIN2 = sem2
BIN3 = sem3

all:
	${CC} -o ${BIN1} ${CFLAGS} ${SRC1} ${LIB}
	${CC} -o ${BIN2} ${CFLAGS} ${SRC2} ${LIB}
	${CC} -o ${BIN3} ${CFLAGS} ${SRC3} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
clean:
	rm -f ${BIN1} ${BIN2} ${BIN3}
	rm -f *.o

.PHONY:
	all clean install uninstall
	
