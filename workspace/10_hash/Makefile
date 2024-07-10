CC = gcc

hash : hash.o
	$(CC) -o $@ $^
	
hash1 : hash1.o
	$(CC) -o $@ $^	

%.o : %.c
	$(CC) -c -o $@ $<
	
clean :
	rm -f *.o hash hash1