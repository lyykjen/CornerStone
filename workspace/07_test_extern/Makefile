CC=gcc
#C flag definitions
CFLAGS 	  = -O3 -Wall -std=gnu99 -I./ -I/usr/include/ #-I/usr/local/include/libusb-1.0 -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib #-lusb-1.0  -lrt -lm -lX11 -lglut -lGL -lGLU
SRC = *.c

LIB = -lpthread

BIN = test

all:
	${CC} -o ${BIN} ${CFLAGS} ${SRC} ${LIB} 
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
clean:
	rm -f ${BIN} 
	rm -f *.o

.PHONY:
	all clean install uninstall
	
