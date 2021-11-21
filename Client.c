#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>//bzero &SIZE
#include <arpa/inet.h>
#define SIZE 1024
#define PORT 20// using port 20

//Function to send the file
void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("CANNOT SEND FILE.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

int main(int argc , char *argv[])
{
	//declaration
	int socket_desc;
	struct sockaddr_in server;
	FILE *fp;
	char *filename = "send.txt";
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("SOCKET COULD NOT BE CREATED!!!");
	}
	else 
	{
		printf("SOCKET CREATED!\n");
	}		
	server.sin_addr.s_addr = inet_addr("192.168.56.5"); // server ip address
	server.sin_family = AF_INET;
	server.sin_port = htons( PORT );

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		printf("CONNECT ERROR!!!");
		return 1;
	}
	
	printf("CONNECTED!\n");
	//OPEN FILE
	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("CANNOT READ FILE.");
		exit(1);
	}
	//CALL SEND FILE FUNCTION
	send_file(fp, socket_desc);
	printf("FILE DATA SENT SUCCESSFULLY.\n");
	printf("CLOSING THE CONNECTION.\n");
	
	//CLOSE client application
	close(socket_desc);
	
	return 0;
}
