#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

enum TYPE{ DATA, ACK, CMD, UP, DOWN, DEL, LIST, EXIT};

typedef	struct	packet{
	uint16_t type;				//Tipo do pacote (p.ex. DATA | ACK | CMD)
	uint16_t seqn;				//Número de sequência
	uint32_t total_size;		//Número total de fragmentos
	uint16_t length;			//Comprimento do payload
	const char*	_payload;		//Dados do pacote
}packet;