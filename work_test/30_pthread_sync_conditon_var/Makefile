CC=gcc

CFLAGS 	  = -O3 -Wall -std=gnu11 -I./ -I/usr/include/ -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib

SRC1 = sync_pthread.c

LIB ?= -lpthread

BIN1 = sync_pthread


all:
	${CC} -o ${BIN1} ${CFLAGS} ${SRC1} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
clean:
	rm -f ${BIN1}
	rm -f *.o

.PHONY:
	all clean install uninstall
	
