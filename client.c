#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 6666 /*server port*/
#define MAXLEN_CITY 29/*max length of city name*/
#define MAXDAY 10/*max number of days*/

int main(int argc, char **argv)
{
	int sockfd,daynum;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE],recvline[MAXLINE],city[MAXLEN_CITY + 1],buffer[MAXLINE];

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
	system("clear");

	while(1){//cityname loop
		memset(sendline, 0, MAXLINE);
		memset(recvline, 0, MAXLINE);
		printf("Welcome to NJUCS Weather Forecast Demo Program!\n");
		printf("Please input City Name in Chinese pinyin(e.g. nanjing or beijing)\n");
		printf("(c)cls,(#)exit\n");
		scanf("%s", &buffer);
		//user selected to exit
		if(buffer[0] == '#' && buffer[1] == '\0'){
			exit(0);
		}
		//clear the screen
		if(buffer[0] == 'c' && buffer[1] == '\0'){
			system("clear");
			continue;
		}

		//validate city name
		sendline[0] = 1;
		strncpy(city, buffer, MAXLEN_CITY);//get the city name from buffer
		strncpy(sendline + 2, city, MAXLEN_CITY);
		send(sockfd, sendline, strlen(sendline + 2) + 2, 0);
		receive(recvline, sockfd);
		if(recvline[0] == 4){
			printf("Sorry, Server does not have weather information for city %s!\n", city);
		}
		else{
			//printf("Valid city.\n");
			system("clear");
			printf("Please enter the given number to query\n");
			printf("1.today\n2.three days from today\n");
			printf("3.custom day by yourself\n(r)back,(c)cls,(#)exit\n");
			printf("===================================================\n");
			while(1){//query choose loop
				scanf("%s", &buffer);

				//invalid input
				if(buffer[1] != 0){
					printf("Input error!\n");
				}
				//user selected to exit
				else if(buffer[0] == '#'){
					exit(0);
				}
				//clear the screen
				else if(buffer[0] == 'c'){
					system("clear");
					printf("Please enter the given number to query\n");
					printf("1.today\n2.three days from today\n");
					printf("3.custom day by yourself\n(r)back,(c)cls,(#)exit\n");
					printf("===================================================\n");
					continue;
				}
				//return
				else if(buffer[0] == 'r'){
					system("clear");
					break;
				}
				//today
				else if(buffer[0] == '1'){
					printf("choose today\n");
				}
				//three days
				else if(buffer[0] == '2'){
					printf("choose three days\n");
				}
				//custom days
				else if(buffer[0] == '3'){
					printf("choose custom day\n");
				}
				//other invalid input
				else{
					printf("Input error!\n");
				}
			}
		}
	}
	exit(0);
}
void receive(char *recvline, int sockfd)
{
	if(recv(sockfd, recvline, MAXLINE, 0) == 0){
		perror("The server terminated prematurely");
		exit(3);
	}
}

