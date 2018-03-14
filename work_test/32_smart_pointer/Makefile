CXX=g++

CXXFLAGS 	= -O3 -Wall --std=c++11 -I./ -I/usr/include/ -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib -lpthread

SRC1 = smart_pointer.cpp
SRC2 = smart_pointer2.cpp

LIB ?= ${LDFLAGS}

BIN1 = smart_pointer
BIN2 = smart_pointer2

all:
	${CXX} ${CXXFLAGS} -o ${BIN1}  ${SRC1} ${LIB}
	${CXX} ${CXXFLAGS} -o ${BIN2}  ${SRC2} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
clean:
	rm -f ${BIN1} ${BIN2}
	rm -f *.o

.PHONY:
	all clean install uninstall
	
