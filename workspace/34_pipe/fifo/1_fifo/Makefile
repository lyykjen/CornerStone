CXX=g++

CXXFLAGS 	= -O3 -Wall --std=c++11 -I./ -I/usr/include/ -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib -lpthread

SRC1 = open_write_fifo.c
SRC2 = open_read_fifo.c

LIB ?= ${LDFLAGS}

BIN1 = write_fifo
BIN2 = read_fifo

all:
	${CXX} ${CXXFLAGS} -o ${BIN1}  ${SRC1} ${LIB}
	${CXX} ${CXXFLAGS} -o ${BIN2}  ${SRC2} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
clean:
	rm -f ${BIN1} ${BIN2}
	rm -f *.o

.PHONY:
	all clean install uninstall
	
