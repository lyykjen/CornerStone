.SUFFIXES: .c .o

CC=gcc
CFLAG= -Wall -g

SRCS1=client.c
SRCS2=server.c

OBJS1=client
OBJS2=server

all: 
	$(CC) -o $(OBJS1) $(CFLAG) $(SRCS1) -lpthread
	$(CC) -o $(OBJS2) $(CFLAG) $(SRCS2) -lpthread
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'

clean:
	-rm -f $(OBJS1) $(OBJS2)
	-rm -f core*

