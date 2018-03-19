CC=gcc

CXXFLAGS 	= -O3 -Wall --std=gnu11 -I./ -I/usr/include/ -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib -lpthread

SRC1 = thread_pool.c
SRC2 = main.c

LIB ?= ${LDFLAGS}

BIN = thread_pool

all:
	${CC} ${CXXFLAGS} -o ${BIN}  ${SRC1} ${SRC2} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
clean:
	rm -f ${BIN}
	rm -f *.o

.PHONY:
	all clean install uninstall
	
