#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//ip serv 192.168.0.111

#define PORTA 2000
void instrucoes();
int ppt();
void inicio(int socketCli);
void jogo(int socketCli);

int main() {

	int socketCli;
	char IP[15];

	printf("Digite o IP do servidor: ");
	scanf("%s", IP);

	struct  sockaddr_in cliA;
	int len_cliA = sizeof(cliA);
	/*Criando socket*/
	socketCli = socket(AF_INET, SOCK_STREAM, 0);

	//Verfica se houve erro de conexão
	if (socketCli == -1){
        perror("Socket ");
        exit(1);
    }

	/*Permite conexão p/ qualquer endereço do host*/
	cliA.sin_family 		= AF_INET;
	cliA.sin_port 			= htons(PORTA);
	cliA.sin_addr.s_addr 	= inet_addr(IP);
	
	memset (&(cliA.sin_zero), 0x00, sizeof (cliA.sin_zero));
	//Fazer Conexão
	if(connect(socketCli, (struct sockaddr *) &cliA, len_cliA) == -1){
		perror("connetc ");
		exit(1);
	}
	
	inicio(socketCli);

	close(socketCli);
	printf("Jogo encerrado.\n");


}

void inicio(int socketCli){
	//char buffer[4096];
	int sel = 0;
		do{
			system("clear");
			printf("Bem vindo!\nDigite:\n1 - Instruções.\n2 - Jogar\n0 - Sair\nEscolha: ");
			scanf("%d", &sel);
			if(sel == 1){
				instrucoes();
			}
			if(sel == 2){
				jogo(socketCli);
				sel = 0;
			}
			if(sel == 0){
				close(socketCli);
			}
		}while(sel != 0);
}
void jogo(int socketCli){
	int res = ppt();
	char res_serv[4096];
	char resC = res+48;
	write(socketCli, &resC, sizeof(res));
	recv(socketCli, &res_serv, sizeof(res_serv), 0);
	printf("%s", res_serv);
	int k;
	for(k=0;k<999999999;k++){}
}

void instrucoes(){
	system("clear");
	char buffer[4096];
	int v;
	strcpy(buffer, "Ola!\nVamos aprender como se joga!\nAqui temos os mesmos principios do jogo real.\nVoce devera escolher uma entre tres opcoes para jogar!\nA sua escolha podera leva-lo a VITORIA!\n\nCombinacoes:\nPedra X Tesoura = Pedra!\nTesoura X Papel = Tesoura!\nPapel X Pedra = Papel!\n>> 0 << para voltar.\0");
	printf("%s\n:", buffer);
	scanf("%d", &v);
	if(v == 0){
		return;
	}
}

int ppt(){
	int tes, jogada;
	char buffer[4096], buffer2[4096];
	do{
		system("clear");
		tes = 0;
		printf("Faça sua Jogada!\n1 - Pedra\n2 - Tesoura\n3 - Papel\nJogada: ");
		scanf("%d", &jogada);
		if((jogada < 1) || (jogada > 3)){
			printf("\nJogada Invalida!\n\nTente Novamente!\n\n");
			tes = 1;
			int k;
			for(k=0;k<999999999;k++){}
		}
	}while(tes);
		return jogada;

	//inicio(socketCli);
}