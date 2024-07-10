CC = gcc

matrix : main.o matrix.o
	$(CC) -o $@ $^
	
%.o : %.c
	$(CC) -c -o $@ $<
	
clean :
	rm -f *.o matrix