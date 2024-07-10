CXX=gcc

CXXFLAGS 	= -O3 -Wall --std=gnu11 -I./ -I/usr/include/ -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib -lpthread -levent

SRC1 = event1.c
SRC2 = event2.c

LIB ?= ${LDFLAGS}

BIN1 = event1
BIN2 = event2

all:
	${CXX} ${CXXFLAGS} -o ${BIN1}  ${SRC1} ${LIB}
	${CXX} ${CXXFLAGS} -o ${BIN2}  ${SRC2} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
clean:
	rm -f ${BIN1} ${BIN2}
	rm -f *.o

.PHONY:
	all clean install uninstall
	
