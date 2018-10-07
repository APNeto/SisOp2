#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <packet.h>

#define PORT 4000
#define MAXPAYLOAD 1500-4*sizeof(uint16_t)

int main(int argc, char *argv[])
{
	int sockfd, n;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	char buf[MAXPAYLOAD];
		
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
	}

/************** Codigo para Upload para o servidor *
//	while (1) {
//		/* receive from socket */
//		n = recvfrom(sockfd, buf, MAXPAYLOAD, 0, (struct sockaddr *) &cli_addr, &clilen);
//		if (n < 0) 
//			printf("ERROR on recvfrom");
//		printf("Received a datagram: %s\n", buf);
//		
//		Ve se arquivo existe
//		FILE *fp;
// 		fp=fopen(buff,"r");
//  		if(fp==NULL)
//   		{
//    		printf("file does not exist\n");
//    	}
//
//		
//		/* send to socket */
//		n = sendto(sockfd, "Got your message\n", 17, 0,(struct sockaddr *) &cli_addr, sizeof(struct sockaddr));
//		if (n  < 0) 
//			printf("ERROR on sendto");
//	}
	
	close(sockfd);
	return 0;
}