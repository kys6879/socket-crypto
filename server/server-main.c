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
unsigned WINAPI HandleClient(void* arg);
void SendMsg(char* msg, int len);

int clientCount = 0;
SOCKET clientSocks[MAX_CLI];
HANDLE hMutex;

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

	HANDLE hThread;

	printf("PORT : %d\n", PORT);
	print_parameter(ECC_CURVE);

	hServSock = socket_env_ready(PORT, &hMutex);


	while (1) {

		szClntAddr = sizeof(clntAddr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
		if (hClntSock == INVALID_SOCKET) {
			ErrorHandling("accept() error");
		}else {
			cli_conn_notification();
		}
		WaitForSingleObject(hMutex, INFINITE);
		clientSocks[clientCount++] = szClntAddr;
		ReleaseMutex(hMutex);
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&hClntSock, 0, NULL);

		printf("Connected Client IP : %s\n", inet_ntoa(clntAddr.sin_addr));
	}

	closesocket(hServSock);
	WSACleanup();

	return 0;
}

unsigned WINAPI HandleClient(void* arg) {
	SOCKET clientSock = *((SOCKET*)arg);
	int strLen = 0, i;
	char msg[BUF_SIZE];

	while ((strLen = recv(clientSock, msg, sizeof(msg), 0)) != 0) {
		// need to write sendMsg func 
	}
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clientCount; i++) {
		if (clientSock == clientSocks[i]) {
			while (i++ < clientCount - 1) {
				clientSocks[i] = clientSocks[i + 1];
			}
			break;
		}
	}
	clientCount--;
	ReleaseMutex(hMutex);
	closesocket(clientSock);
	return 0;
}

void SendMsg(char* msg, int len) {
	int i;
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clientCount; i++) {
		send(clientSocks[i], msg, len, 0);
	}
	ReleaseMutex(hMutex);
}

void cli_conn_notification() {
	printf("client Á¢¼Ó ! : ");
	printCurrentTime();
}
