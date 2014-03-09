all: client server
client: client.c
	gcc -Wall -pedantic -std=c99 -g -c client.c -o client.out
server: server.c
	gcc -Wall -pedantic -std=c99 -g -c server.c -o server.out
clean:
	rm -rf *.o
	rm -rf *.out

