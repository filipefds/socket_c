#include <stdio.h>	// biblioteca para entrada e saída de dados
#include <sys/socket.h> // biblioteca para uso de socket
#include <netinet/in.h> // biblioteca para adicionar IP e porta ao socket
#include <unistd.h>	// biblioteca para utilizar a função close
#include <string.h>	// biblioteca para manipular strings

#define LEN 4096 	// Define com uma constante o tamanho do buffer

int main () {

	struct sockaddr_in serv_addr; 
	int listenfd = 0;
	char buffer[LEN];
        
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(5000);


	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_id == -1) {
		printf("Erro ao criar o socket.\n");
		return 1;
	} else printf ("Socket: OK!\n");

	int bind_status = bind(socket_id, (struct sockaddr *) &serv_addr, sizeof serv_addr);
	if (bind_status == -1) {
		printf("Bind falhou.");
		return 1;
	}else printf("Bind: OK!\n");

	// Listen coloca o Socket em estado de escuta.
	if (listen(socket_id, 50) != 0) {
		printf("Erro ao iniciar o servidor.\n");
		return 1;
	} else 	printf("Servidor iniciado e aguardando...\n.");

	int ssize = sizeof serv_addr;

	while (1) {

		int novo_socket  = accept(socket_id, (struct sockaddr *) &serv_addr, &ssize);
		int count_r = recv(novo_socket, buffer, LEN, 0);

	        send(novo_socket, buffer, strlen(buffer), 0);

		fflush(stdout);

		close(novo_socket);

	}

	return 0;

}
