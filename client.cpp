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
#include <fstream>

#define MAXPAYLOAD 1500 - 4 * sizeof(uint16_t)
#define MAXNAME 256

char username[MAXNAME];
char path_to_syncdir[MAXNAME * 2];

int uploadfile(std::string filename)
{
	char buffer[MAXPAYLOAD];
	int sockfd, n;
	struct sockaddr_in serv_addr;
	int i = 0;
	char *memblock;
	double size;

	std::cout << "Em uploadfile" << std::endl;

	std::ifstream myfile(filename.c_str(), std::ifstream::in);

	// avisar servidor que vamos subir arquivo com nome "filename"
	sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));
	if (myfile.is_open())
	{
		myfile.seekg(0, std::ios::end);
		auto filesize = (double)myfile.tellg();
		myfile.seekg(0, std::ios::beg);
		std::cout << filesize;
		int ab = (int)filesize % MAXPAYLOAD;
		while (filesize > MAXPAYLOAD)
		{
			myfile.read(buffer, MAXPAYLOAD);
			std::cout << "\nREAD:" << strlen(buffer) << "\n"
					  << "SENT:";
			n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));

			if (n < 0)
				printf("ERROR sendto");
			printf("Got an ack: %s\n", buffer);

			filesize = filesize - MAXPAYLOAD;
			std::cout << n << "\n";
		}
		myfile.read(buffer, MAXPAYLOAD);
		n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));
		std::cout << "HI" << std::endl;
	}
	else
	{
		std::cout << "\nFILE COULD NOT BE OPENED \n";
	}
	return 0;
}

int downloadfile(std::string filename)
{
	int sockfd, n;
	char buffer[MAXPAYLOAD];
	unsigned int length;
	struct sockaddr_in from;
	std::cout << "Em downloadfile" << std::endl;
	// enviar comando e nome do arquivo para servidor
	// receber resposta de servidor de que arquivo existe
	// abrir arquivo em modo de escrita
	// receber pacotes de servidor e escrever conteudo no arquivo
	std::ofstream myfile(filename.c_str(), std::ofstream::out);
	if(!myfile)
	{
		std::cerr << "Oops! File could not be opened for writing" << std::endl;
	}
	
	n = recvfrom(sockfd, buffer, 256, 0, (struct sockaddr *) &from, &length);
	if(n > 0) {
		std::cout << "ERROR recv on downloadfile\n";
		return -1;
	}
	myfile << buffer;
	return 0;
}
int deletefile(std::string filename)
{
	std::string filename;
	std::cout << filename;
	std::cout << "Em deletefile" << std::endl;
	// ver se arquivo existe em sync_dir
	// apagar arquivo localmente - feito
	// enviar comando e nome do arquivo para servidor
	// talvez desnecessario - receber confirmacao de remocao do arquivo do servidor e informar usuario

	if (remove(filename.c_str()) == 0) {
    // success, print something
		std::cout << "File removed from client" << std::endl;

		// Pacote do tipo CMD representando comando Delete enviado ao servidor
		//sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));

	} else {
    // failure
    std::cout << "\nCan't remove " << filename << ": "
         << strerror(errno) << std::endl;
	}
	return 0;
}

int list_server()
{
	std::cout << "Em list_server" << std::endl;
	// enviar comando para servidor
	// obter resposta de arquivos presentes em servidor
	// exibir lista de arquivos para usuario
	return 0;
}
int list_client()
{
	std::cout << "Em list_client" << std::endl;
	//abrir pasta sync_dir
	// exibir lista de arquivos para usuario
	return 0;
}
int get_sync_dir()
{
	std::cout << "Em get_sync_dir" << std::endl;
	//
	return 0;
}
int exit()
{
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		std::cout << "Argumentos fornecidos nao correspondentes. Formato aceito: \n"
				  << "./myClient <username> <server_ip_address> <port>\n";
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
	std::cout << PORT << "\n";
	char buffer[MAXPAYLOAD];

	//-----
	//Ver melhor a parte de estabelecer conexão
	//----=
	server = gethostbyname(argv[2]);
	if (server == NULL)
	{
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		printf("ERROR opening socket");
	std::cout << "Opened socket\n";

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr = *((struct in_addr *)server->h_addr);
	bzero(&(serv_addr.sin_zero), 8);

	// -----
	//Preparar o caminho pro sync_dir
	//COMO O PORCO FEZ:
	// const char* homedir;
    // if ((homedir = getenv("HOME")) == nullptr) {
    //     homedir = getpwuid(getuid())->pw_dir;
    // }
    // sprintf(path_to_syncdir, "%s/sync_dir_%s", homedir, username);
    // create_dir(path_to_syncdir);
	//^^^^^^
	//-----

	//Depois preparar o a sincronização da pasta

	//Sincronização inicial

	//Criação de 3 threads
	//1º To listen on socket
	//2º upload files
	//3º download files

	//Dps o porco chamou uma função que seria somento o while pra receber os comandos

	std::string comand;

	while (1)
	{
		std::cin.clear();
		std::getline(std::cin, comand);
		if (comand == "upload")
		{
			uploadfile("teste.txt");
			continue;
		}
		if (comand == "download")
		{
			downloadfile("texte.txt");
			continue;
		}
		if (comand == "delete")
		{
			deletefile("teste.txt");
			continue;
		}
		if (comand == "list_client")
		{
			list_client();
			continue;
		}
		if (comand == "list_server")
		{
			list_server();
			continue;
		}
		if (comand == "get_sync_dir")
		{
			get_sync_dir();
			continue;
		}
		if (comand == "exit")
		{
			exit();
			continue;
		}
		std::cout << "Comando invalido\n";
	}

	close(sockfd);
	return 0;
}