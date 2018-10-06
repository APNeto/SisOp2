#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <string>

int uploadfile(){return 0;}
int downloadfile(){return 0;}
int deletefile(){return 0;}
int list_server(){return 0;}
int list_client(){return 0;}
int get_sync_dir(){return 0;}
int exit(){return 0;}

int main(int argc, char *argv[])
{
    if(argc != 4){
        std::cout << "Argumentos fornecidos nao correspondentes. Formato aceito: \n" <<
            "./myClient <username> <server_ip_address> <port>\n";
        exit(1);
    }

    int PORT = atoi(argv[3]);;

    int sockfd, n;
	unsigned int length;
	struct sockaddr_in serv_addr, from;
	struct hostent *server;
	
	char buffer[256];
	if (argc < 2) {
		fprintf(stderr, "usage %s hostname\n", argv[0]);
		exit(0);

	}
	
	server = gethostbyname(argv[2]);
	if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

	std::string comand;
	std::cin >> comand;
	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		printf("ERROR opening socket");
	
	serv_addr.sin_family = AF_INET;     
	serv_addr.sin_port = htons(PORT);    
	serv_addr.sin_addr = *((struct in_addr *)server->h_addr);
	bzero(&(serv_addr.sin_zero), 8);  

	printf("Enter the message: ");
	bzero(buffer, 256);
	fgets(buffer, 256, stdin);

	n = sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *) &serv_addr, sizeof(struct sockaddr_in));
	if (n < 0) 
		printf("ERROR sendto");
	
	length = sizeof(struct sockaddr_in);
	n = recvfrom(sockfd, buffer, 256, 0, (struct sockaddr *) &from, &length);
	if (n < 0)
		printf("ERROR recvfrom");

	printf("Got an ack: %s\n", buffer);

	while(1){
		switch(comand){
			case "upload": uploadfile(); break;
			case "download": downloadfile(); break;
			case "delete": deletefile(); break;
			case "list_client": list_client(); break;
			case "list_server": list_server(); break;
			case "get_sync_dir": get_sync_dir(); break;
			case "exit": exit(); break;
			default: std::cout << "Comando invalido\n";
		}
	}
	
	close(sockfd);
	return 0;
}