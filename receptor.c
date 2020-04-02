#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char** argv)
{

	int server_fd, port, recv_bytes;   //file descriptor do socket, porta e bytes recebidos
	char buffer;     // buffer que armazenara caracter recebido
	struct sockaddr_in server_addr;

	porta = atoi(argv[1]); //porta a ser enviada recebido como parametro

	server_fd = socket(AF_INET, SOCK_DGRAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(porta);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

	FILE *pf = fopen("recebido.txt", "wb"); //abre o arquivo a ser escrito
    if (pf == NULL){
    printf("Falha ao abrir o arquivo!\n");
    }

	do{
		recv_bytes = recvfrom(server_fd, &buffer, 1, MSG_WAITALL,
							  NULL, NULL); /
		fwrite(&buffer, sizeof(char), 1, pf);

	}while(recv_bytes != 0);

	fclose(pf);

	return 0;
}