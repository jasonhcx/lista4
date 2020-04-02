#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char **argv)
{

	int client_fd, porta;	  //file descriptor do socket, porta recebida como parametro
	char buffer;			  //buffer que armazena o caracter a ser enviado
	char *host = argv[2]; //endereco para quem vai ser enviado o arquivo recebido como parametro
	struct sockaddr_in server_addr;

	porta = atoi(argv[3]); //porta a ser enviada recebido como parametro

	client_fd = socket(AF_INET, SOCK_DGRAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(porta);
	inet_aton(host, &server_addr.sin_addr);

	FILE *pf = fopen(argv[1], "r"); //abre o arquivo a ser enviado recebido como parametro
    if (pf == NULL){
    printf("Falha ao abrir o arquivo!\n");
    }

	while (fread(&buffer, sizeof(char), 1, pf) != 0){
		sendto(client_fd, &buffer, 1, 0, (struct sockaddr *)&server_addr,
			   (unsigned int)sizeof(server_addr));										  
	}

	sendto(client_fd, NULL, 0, 0, (struct sockaddr *)&server_addr,
		   (unsigned int)sizeof(server_addr));

	fclose(pf);

	return 0;
}