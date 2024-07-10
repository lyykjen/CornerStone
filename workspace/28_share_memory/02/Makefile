CC=gcc

CFLAGS 	  = -O3 -Wall -std=gnu11 -I./ -I/usr/include/ -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib

SRC0 = semaphore.c frame.c
SRC1 = producer.c ${SRC0}
SRC2 = consumer.c ${SRC0}

LIB ?= 

BIN1 = producer
BIN2 = consumer

TARGET = ${BIN1} ${BIN2}

all:
	${CC} -o ${BIN1} ${CFLAGS} ${SRC1} ${LIB}
	${CC} -o ${BIN2} ${CFLAGS} ${SRC2} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
clean:
	rm -f ${TARGET}
	rm -f *.o

.PHONY:
	all clean install uninstall
	
