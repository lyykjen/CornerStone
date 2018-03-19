CC=gcc

CFLAGS 	  = -O3 -Wall -std=gnu11 -I./ -I/usr/include/ -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib
SRC = *.c

LIB ?= 

BIN = va_args

all:
	${CC} -o ${BIN} ${CFLAGS} ${SRC} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
clean:
	rm -f ${BIN} 
	rm -f *.o

.PHONY:
	all clean install uninstall
	
