#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORTA 2000
void *win(void *sock);
int main(){
	
	//Variáveis
	struct  sockaddr_in servA, cliA;
	int socketServ, socketCli;
	int len_cliA = sizeof(cliA);

	/*Criando socket*/
	socketServ = socket(AF_INET, SOCK_STREAM, 0);

	//Verfica se houve erro de conexão
	if (socketServ == -1){
        perror("Socket ");
        exit(1);
    }else{
    	printf("Socket criado com Sucesso!\n");
    }

	/*Permite conexão p/ qualquer endereço do host*/
	servA.sin_family 		= AF_INET;
	servA.sin_addr.s_addr 	= INADDR_ANY;
	servA.sin_port 			= htons(PORTA);
	
	//Verificaçao de erro ao gerar porta
	if (bind(socketServ,(struct sockaddr *) &servA, sizeof(servA)) == -1){
        perror("Bind ");
        exit(1);
    }

    /* receber conexao */
	listen(socketServ, 50);
	int i = -1;
	pthread_t thread_id[100];
	while(socketCli = accept(socketServ, (struct sockaddr *) &cliA, &len_cliA)){
		i += 1;
		//Aceitando conexão		
		printf("Novo Jogador Conectado!\n");
		//win(socketCli);

		if( pthread_create( &thread_id[i] , NULL ,  win , (void*) &socketCli) < 0){
			perror("Não foi possivel criar a thread!!!");
				return 1;
		}
		if (socketCli < 0){
	        	perror("Falha ao conectar!!!");
	        	return 1;
	    }
	}
}

void *win(void *sock){
		int socketCli = *(int*)sock;
	//////////////////////////////////////////////////////////	
		char mensagem, *resposta;
		read(socketCli, &mensagem, sizeof(mensagem));
		int jServ, resul;
		srand(time(NULL));
		jServ = 1 + (rand() % 3);

		if((mensagem-48) == jServ) resul = 0;
		if((mensagem == '1') && (jServ == 2)) resul = 1;
		if((mensagem == '2') && (jServ == 3)) resul = 1;
		if((mensagem == '3') && (jServ == 1)) resul = 1;
		if((jServ == 1) && (mensagem == '2')) resul = 2;
		if((jServ == 2) && (mensagem == '3')) resul = 2;
		if((jServ == 3) && (mensagem == '1')) resul = 2;
///////////////////////////////////////////////////////////
		if (resul == 0){
			resposta = "Empate!\n";
			//printf("%s\n", resposta);
			write(socketCli, resposta, strlen(resposta));
		}
		if (resul == 1){
			resposta = "Você foi o vencedor! PARABÉNS!\n";
			//printf("%s\n", resposta);
			write(socketCli, resposta, strlen(resposta));
		}
		if (resul == 2){
			resposta = "Que pena! Não foi desta vez!\n";
			//printf("%s\n", resposta);
			write(socketCli, resposta, strlen(resposta));
		}
///////////////////////////////////////////////////////////
}