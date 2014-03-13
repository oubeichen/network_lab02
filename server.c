#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<time.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 6666 /*port*/
#define LISTENNQ 8 /*maximum number of client connections*/
#define MAXLEN_CITY 29 /*max length of city name*/
#define MAXCITY_NUM 30 /*maximum number of cities*/
#define SEND_SIZE 137/*length of receiving package's data*/

int main(int argc, char **argv)
{
	int listenfd, connfd, n, citynum = 3, i;
	pid_t childpid;
	socklen_t clilen;
	char recvline[MAXLINE],sendline[MAXLINE],cities[MAXCITY_NUM][MAXLEN_CITY + 1] = {"nanjing", "beijing", "shanghai"};
	struct sockaddr_in cliaddr, servaddr;
	time_t now;
	struct tm *date;

	//Create a socket for the soclet
	//If sockfd<0 there was error in the creation of the socket
	if((listenfd = socket (AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Problem in creating the socket");
		exit(1);
	}

	//preparation of the socket address
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	//bind the socket
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	//listen to the socket by creating a connection queue, then wait for clients
	listen(listenfd, LISTENNQ);
	printf("Server running...witing for connections.\n");

	while(1){
		clilen = sizeof(cliaddr);
		//accpet a connection
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

		printf("Received request...\n");

		if((childpid = fork()) == 0){//if it's zero, it's child process
			printf("Child created for dealing with client requests.\n");

			//close listening socket
			close(listenfd);

			for(; (n = recv(connfd, recvline, MAXLINE,0)) > 32;
					send(connfd, sendline, SEND_SIZE,0), 
					memset(recvline, 0, MAXLINE),memset(sendline, 0, MAXLINE)){//valid length
				printf("received a line\n");

				strncpy(sendline + 2, recvline + 2, MAXLEN_CITY);
				if(recvline[0] == 1)//validate city
				{
					for(i = 0;i < citynum;i++){
						printf("%s, %s\n",sendline + 2, cities[i]);
						if(strcmp(sendline + 2, cities[i]) == 0)
							break;
					}
					if(i == citynum)//city not found
					{
						sendline[0] = 4;
					}else{
						sendline[0] = 3;
					}

				}else if(recvline[0] == 2){

					time(&now);
					date = localtime(&now);
				}else{
					sendline[0] = 5;
				}

			}

			if(n < 0)
				printf("Read error!\n");
			printf("Client disconnected..,\n");
			exit(0);
		}
		close(connfd);
	}
}

