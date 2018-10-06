#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>

#define PORT 4000

int uploadfile(){return 0;}
int downloadfile(){return 0;}
int deletefile(){return 0;}
int list_server(){return 0;}
int list_client(){return 0;}
int get_sync_dir(){return 0;}
int exit(){return 0;}

int main(int argc, char *argv[])
{
	int sockfd, n;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	char buf[256];
		
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
		printf("ERROR opening socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(serv_addr.sin_zero), 8);    
	 
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) < 0) 
		printf("ERROR on binding");
	
	clilen = sizeof(struct sockaddr_in);
	
	while (1) {
		/* receive from socket */
		n = recvfrom(sockfd, buf, 256, 0, (struct sockaddr *) &cli_addr, &clilen);
		if (n < 0) 
			printf("ERROR on recvfrom");
		printf("Received a datagram: %s\n", buf);
		
		/* send to socket */
		n = sendto(sockfd, "Got your message\n", 17, 0,(struct sockaddr *) &cli_addr, sizeof(struct sockaddr));
		if (n  < 0) 
			printf("ERROR on sendto");

//****** Cria thread
		pthread_create(&sync_info.thr_send[device.device_id], nullptr, send_to_client, &device);
+    	pthread_create(&sync_info.thr_recv[device.device_id], nullptr, recv_from_client, &device)
	}
	close(sockfd);
	return 0;
}