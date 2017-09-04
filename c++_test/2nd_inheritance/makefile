.SUFFIXES: .c .o

CC=g++
CFLAG= -Wall -g -std=gnu++11

SRCS1=inheritance.cpp
SRCS2 ?=

OBJS1=inheritance
OBJS2 ?=

all: 
	$(CC) -o $(OBJS1) $(CFLAG) $(SRCS1)
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'

clean:
	-rm -f $(OBJS1)
	-rm -f core*

