#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define CLIENT

#include <stdio.h>
#include <stdio.h>
#include <WinSock2.h>
#include <time.h>
#include <stdint.h>

#include "socket.h" 
#include "handler.h"

#define PORT 3000
#define ADDRESS "127.0.0.1"
#define BUF_SIZE 100
#define NAME_SIZE 20

char name[NAME_SIZE] = "[DEFAULT]";

char msg[BUF_SIZE];
char inputName[100];

unsigned WINAPI SendMsg(void* arg);
unsigned WINAPI RecvMsg(void* arg);

int main() {

	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char r_msg[30];

	uint8_t s_msg[30];
	uint8_t flag[3];

	int strLen;

	HANDLE sendThread, recvThread;

	printf("Input your name : ");
	gets(inputName);
	sprintf(name, "[%s]", inputName);

	
	hSocket = socket_env_ready(PORT, ADDRESS);

	printf("성공\n");
	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSocket, 0, NULL);//메시지 전송용 쓰레드가 실행된다.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSocket, 0, NULL);//메시지 수신용 쓰레드가 실행된다.

	WaitForSingleObject(sendThread, INFINITE);
	WaitForSingleObject(recvThread, INFINITE);

	closesocket(hSocket); //소켓 라이브러리 해제
	WSACleanup();
	system("pause");

	return 0;
}

unsigned WINAPI SendMsg(void* arg) {
	SOCKET sock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	while (1) {
		fgets(msg, BUF_SIZE, stdin);
		if (strcmp(msg, "q\n")) {
			send(sock, "q", 1, 0);
		}
		sprintf(nameMsg, "%s %s", name, msg);
		send(sock, nameMsg, strlen(nameMsg), 0);
	}
	return 0;
}
unsigned WINAPI RecvMsg(void* arg) {
	SOCKET sock = *((SOCKET *)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	int strLen;
	while (1) {
		strLen = recv(sock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);
		if (strLen == -1)
			return -1;
		nameMsg[strLen] = 0;
		if (!strcmp(nameMsg, "q")) {
			printf("left the chat\n");
			closesocket(sock);
			exit(0);
		}
		fputs(nameMsg, stdout);
	}
	return 0;

}