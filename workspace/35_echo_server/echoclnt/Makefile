CXX=g++

CXXFLAGS 	= -O3 -Wall --std=c++11 -I./ -I/usr/include/ -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib -lpthread

SRC1 = echoclnt.c
SRC2 = helper.c

LIB ?= ${LDFLAGS}

BIN = echoclnt

all:
	${CXX} ${CXXFLAGS} -o ${BIN}  ${SRC1} ${SRC2} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
clean:
	rm -f ${BIN}
	rm -f *.o

.PHONY:
	all clean install uninstall
	
