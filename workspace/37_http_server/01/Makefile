# Taken from http://www.cnblogs.com/life2refuel/p/7154961.html

all:httpd client

httpd : httpd.c
	gcc -g -Wno-unused-result -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Wall -O2 -o $@ $^ -lpthread

client : client.c
	gcc -g -Wall -o $@ $^

clean:
	rm -rf httpd client