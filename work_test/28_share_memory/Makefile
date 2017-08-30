CC=gcc

CFLAGS 	  = -O3 -Wall -std=gnu11 -I./ -I/usr/include/ -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib

SRC1 = shmread.c
SRC2 = shmwrite.c

LIB ?= 

BIN1 = readshm
BIN2 = writeshm

all:
	${CC} -o ${BIN1} ${CFLAGS} ${SRC1} ${LIB}
	${CC} -o ${BIN2} ${CFLAGS} ${SRC2} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
clean:
	rm -f ${BIN1} ${BIN2}
	rm -f *.o

.PHONY:
	all clean install uninstall
	
