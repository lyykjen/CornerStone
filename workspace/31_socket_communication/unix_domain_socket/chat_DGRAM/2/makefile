.SUFFIXES: .c .o

CC=g++
CFLAG= -Wall -g

SRCS1=client.cc
SRCS2=server.cc

OBJS1=client
OBJS2=server

all: 
	$(CC) -o $(OBJS1) $(CFLAG) $(SRCS1) -lpthread
	$(CC) -o $(OBJS2) $(CFLAG) $(SRCS2) -lpthread
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'

clean:
	-rm -f $(OBJS1) $(OBJS2)
	-rm -f core*

