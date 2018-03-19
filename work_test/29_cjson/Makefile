CC=gcc

CFLAGS 	  = -O3 -Wall -std=gnu11 -I./ -I/usr/include/ -Wfatal-errors
LDFLAGS		= -L./ -L/usr/local/lib -L/usr/lib

SRC1 = 0_test_json.c cJSON.c
SRC2 = yeelink_cjson.c cJSON.c
SRC3 = 1_test_json.c cJSON.c
SRC4 = 2_test_json.c cJSON.c
SRC5 = 3_test_json.c cJSON.c

LIB ?= -lm

BIN1 = 0_test_json
BIN2 = yeelink
BIN3 = 1_test_json
BIN4 = 2_test_json
BIN5 = 3_test_json

all:
	${CC} -o ${BIN1} ${CFLAGS} ${SRC1} ${LIB}
	${CC} -o ${BIN2} ${CFLAGS} ${SRC2} ${LIB}
	${CC} -o ${BIN3} ${CFLAGS} ${SRC3} ${LIB}
	${CC} -o ${BIN4} ${CFLAGS} ${SRC4} ${LIB}
	${CC} -o ${BIN5} ${CFLAGS} ${SRC5} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'

yeelink:
	${CC} -o ${BIN2} ${CFLAGS} ${SRC2} ${LIB}
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
0:
	${CC} -o ${BIN1} ${CFLAGS} ${SRC1} ${LIB}	
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
1:
	${CC} -o ${BIN3} ${CFLAGS} ${SRC3} ${LIB}	
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
2:
	${CC} -o ${BIN4} ${CFLAGS} ${SRC4} ${LIB}	
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'
3:
	${CC} -o ${BIN5} ${CFLAGS} ${SRC5} ${LIB}	
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'	

clean:
	rm -f ${BIN1} ${BIN2} ${BIN3} ${BIN4} ${BIN5}
	rm -f *.o

.PHONY:
	all clean install uninstall
	
