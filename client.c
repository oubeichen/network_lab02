#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 6666 /*server port*/
#define MAXLEN_CITY 20/*max length of city name*/
#define MAXDAY 10/*max number of days*/

int main(int argc, char **argv)
{
	int sockfd,choice,daynum;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE],recvline[MAXLINE],city[MAXLEN_CITY],buffer[MAXLINE];

	//Create a socket for the client
	//If sockfd<0 there was an error in the creation of the socket
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Problem in creating the socket.");
		exit(1);
	}

	//Creation of the socket
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	/*
	 if(argc == 2){
	      servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	 }else{
	      servaddr.sin_addr.s_addr = inet_addr("114.212.191.33");
	 }
	 */
	servaddr.sin_addr.s_addr = inet_addr("114.212.191.33");
	servaddr.sin_port = htons(SERV_PORT);//convert to big-endian order

	//Connection of the client to the socket
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
		perror("Problem in connecting to the server");
		exit(2);
	}

	while(1){
		printf("Welcome to NJUCS Weather Forecast Demo Program!\nPlease input City Name in Chinese pinyin(e.g. nanjing or beijing)\n(c)cls,(#)exit\n");
		scanf("%s",&buffer);
		if(buffer[0] == '#' && buffer[1] == '\0'){
			break;
		}
		memset(sendline, 0, MAXLINE);
		memset(recvline, 0, MAXLINE);
	}
	exit(0);
}

