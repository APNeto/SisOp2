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

int uploadfile(){
	std::cout<<"Em uploadfile"<< std::endl;

//	n = sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *) &serv_addr, sizeof(struct sockaddr_in));
//	if (n < 0) 
//		printf("ERROR sendto");
//	
//	length = sizeof(struct sockaddr_in);
//	n = recvfrom(sockfd, buffer, 256, 0, (struct sockaddr *) &from, &length);
//	if (n < 0)
//		printf("ERROR recvfrom");
//
//	printf("Got an ack: %s\n", buffer);

	return 0;
}

int downloadfile(){
	std::cout<<"Em downloadfile"<< std::endl;
	return 0;
	}
int deletefile(){return 0;}
int list_server(){return 0;}
int list_client(){return 0;}
int get_sync_dir(){return 0;}
int exit(){return 0;}

#define MAXNAME 256

char username[MAXNAME];
char path_to_syncdir[MAXNAME*2];

int main(int argc, char *argv[])
{
    if(argc < 4){
        std::cout << "Argumentos fornecidos nao correspondentes. Formato aceito: \n" <<
            "./myClient <username> <server_ip_address> <port>\n";
        exit(1);
    }

    int sockfd, n;
	unsigned int length;
	struct sockaddr_in serv_addr, from;
	struct hostent *server;
	char hostname[MAXNAME];
	uint16_t PORT;

	strcpy(username, argv[1]);
    strcpy(hostname, argv[2]);
    PORT = atoi(argv[3]);
	std::cout << PORT<<"\n";
	char buffer[256];
	server = gethostbyname(argv[2]);
	if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		printf("ERROR opening socket");
	std::cout << "Opened socket\n";
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr = *((struct in_addr *)server->h_addr);
	bzero(&(serv_addr.sin_zero), 8);
	
	printf("Enter the message:\n");
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

//	while(1){
//		if(comand == "upload"){
//			uploadfile(); continue;
//		}
//		if(comand == "download"){
//			downloadfile(); continue;
//		}
//		if(comand == "delete"){
//			deletefile(); continue;
//		}
//		if(comand == "list_client"){
//			list_client(); continue;
//		}
//		if(comand == "list_server"){
//			list_server(); continue;
//		}
//		if(comand == "get_sync_dir"){
//			get_sync_dir(); continue;
//		}
//		if(comand == "exit"){
//			exit(); continue;
//		}
//		std::cout << "Comando invalido\n";
//	}

	close(sockfd);
	return 0;
}