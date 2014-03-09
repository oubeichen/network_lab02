all: client server
client: client.c
	gcc -Wall -pedantic -std=c99 -g client.c -o client.out
server: server.c
	gcc -Wall -pedantic -std=c99 -g server.c -o server.out
clean:
	rm -rf *.o
	rm -rf *.d
	rm -rf *.out

