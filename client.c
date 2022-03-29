#include <stdio.h>      // biblioteca para entrada e saída de dados
#include <sys/socket.h> // biblioteca para uso de socket
#include <netinet/in.h> // biblioteca para adicionar IP e porta ao socket
#include <unistd.h>     // biblioteca para utilizar a função close
#include <arpa/inet.h>	// biblioteca para utilizar inet_addr para informar o IP do servidor
#include <string.h>	// biblioteca para manipular strings

#define LEN 4096

int main () {

        struct sockaddr_in client_addr;
	char buffer_in[LEN];
	char buffer_out[LEN];

        client_addr.sin_family = AF_INET;
        client_addr.sin_addr.s_addr = inet_addr("10.2.0.143");
        client_addr.sin_port = htons(5000);

	int socket_id = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(socket_id, (struct sockaddr *) &client_addr, sizeof client_addr) != 0){
		printf("Conexão falhou!\n");
		return 1;
	} else printf("Conectado ao servidor...\n");

	fflush(stdin);

	memset(buffer_in, 0x0, LEN);
        memset(buffer_out, 0x0, LEN);

	printf("Cliente: ");
	fgets(buffer_out, LEN, stdin);
	
       	send(socket_id, buffer_out, strlen(buffer_out), 0);

	int slen = recv(socket_id, buffer_in, LEN, 0);
	buffer_in[slen + 1] = '\0';
	fprintf(stdout, "Servidor: %s\n", buffer_in);

	fflush(stdout);

        close(socket_id);

	return 0;

}
