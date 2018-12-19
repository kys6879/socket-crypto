#define _CRT_SECURE_NO_WARNINGS
#define SERVER

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <WinSock2.h>
#include <time.h>


#include "handler.h"
#include "socket.h"
#include "log.h"
#include "ecc.h"
#include "content.h"
#include "hash.h"

#define PORT 3000
#define BUF_SIZE 100
#define MAX_CLI 5

void cli_conn_notification();

int clientCount = 0;


int main() {
	
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN clntAddr;

	int szClntAddr;
	int i;
	int *p;
	int a = 5;
	int errCode = 0;
	int length;
	char send_message[] = "i am server!";
	uint8_t flag[3];
	uint8_t r_msg[30];
	unsigned char  encrypt[32];

	uint8_t cli_pub[ECC_BYTES + 1];
	uint8_t cli_pri[ECC_BYTES];


	printf("PORT : %d\n", PORT);
	print_parameter(ECC_CURVE);

	hServSock = socket_env_ready(PORT);


	while (1) {

		szClntAddr = sizeof(clntAddr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
		if (hClntSock == INVALID_SOCKET) {
			ErrorHandling("accept() error");
		}else {
			cli_conn_notification();
		}

		FILE *fp = fopen("msg.txt", "a");

		recv(hClntSock, r_msg, sizeof(r_msg), 0);

		hash_sha256(r_msg, encrypt);

		for (i = 0; i < 32; i++) {
			fprintf(fp,"%02x", encrypt[i]);
		}
		fprintf(fp, "\n");
	
		//fputs(r_msg, fp);   // 파일에 문자열 저장
		fclose(fp);

		printf("전달받은 문자열 : %s\n", r_msg);
		
	}

	return 0;
}

void cli_conn_notification() {
	printf("client 접속 ! : ");
	printCurrentTime();
}
