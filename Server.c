#include<stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<string.h> // starlen
#include<unistd.h> // write
#define PORT 20
#define SIZE 1024

void write_file(int sockfd){
  int n;
  FILE *fp;
  char *filename = "recv.txt";
  char buffer[SIZE];

  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  return;
}

int main(int argc , char *argv[])
{
	//declaration
	int socket_desc, new_socket , new_sock;
	struct sockaddr_in server, new_addr; 
	socklen_t addr_size;
	char buffer[SIZE];

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("COULD NOT CREATE SOCKET");
	}
		
	server.sin_addr.s_addr = INADDR_ANY; //Please enter the ip address of your Server VM
	server.sin_family = AF_INET;
	server.sin_port = htons( PORT );


	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		printf("ERROR BINDING SOCKET TO PORT %d \n", PORT);
		return 1;
	}
	puts("Binding successfull.");
	
	
	//Listen
	if(listen(socket_desc, 10) == 0){
		printf("Listening....\n");
	}else{
		perror("ERROR IN LISTENING!!!");
    exit(1);
	}

	if (new_socket<0)
	{
		perror("ACCEPT FAILED");
		return 1;
	}

	addr_size = sizeof(new_addr);
	new_sock = accept(socket_desc, (struct sockaddr*)&new_addr, &addr_size);
	write_file(new_sock);
	printf("DATA TRANSFERRED SUCCESFULLY.\n");
	return 0;
}